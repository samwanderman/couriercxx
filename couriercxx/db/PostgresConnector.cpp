/*
 * PostgresConnector.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "PostgresConnector.h"

#include <pqxx/binarystring.hxx>
#include <pqxx/connection_base.hxx>
#include <pqxx/prepared_statement.hxx>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include <cstdarg>
#include <cstdio>
#include <utility>

#define BUFFER_SIZE	1024

template<class T>
pqxx::prepare::invocation& prep_dynamic(T data, pqxx::prepare::invocation& inv) {
	inv(data);
	return inv;
}

PostgresConnector::PostgresConnector(std::string host, uint16_t port, std::string username, std::string password, std::string dbName, std::string encoding) {
	this->host = host;
	this->port = port;
	this->username = username;
	this->password = password;
	this->dbName = dbName;
	this->encoding = encoding;
	connection = nullptr;
}

PostgresConnector::~PostgresConnector() {
	close();
}

int PostgresConnector::open() {
	if (opened) {
		return -1;
	}

	char buffer[BUFFER_SIZE];
	sprintf(buffer, "host=%s port=%u user=%s password=%s dbname=%s\r\n", host.c_str(), port, username.c_str(), password.c_str(), dbName.c_str());
	connection = new pqxx::connection(buffer);
	if (!connection->is_open()) {
		close();

		return -1;
	}
	connection->set_client_encoding(encoding);

	opened = true;

	return 0;
}

int PostgresConnector::close() {
	if (!opened) {
		return -1;
	}

	if (connection != nullptr) {
		if (connection->is_open()) {
			connection->disconnect();
		}

		delete connection;
		connection = nullptr;
	}

	opened = false;

	return 0;
}

bool PostgresConnector::isOpen() {
	return opened && connection->is_open();
}

int PostgresConnector::addStatement(std::string name, std::string sql, std::list<std::type_index> types) {
	connection->prepare(name, sql);
	preparedStatements.insert(std::pair<std::string, std::list<std::type_index>>(name, types));

	return 0;
}

int PostgresConnector::addStatement(std::string name, std::string sql) {
	std::list<std::type_index> types;

	return addStatement(name, sql, types);
}

pqxx::result PostgresConnector::execStatement(std::string name, ...) {
	accessMutex.lock();
	va_list args;
	va_start(args, name);

	pqxx::work worker(*connection);
	pqxx::prepare::invocation invoke = worker.prepared(name);
	pqxx::result res;

	std::list<std::type_index> types;
	std::map<std::string, std::list<std::type_index>>::iterator it = preparedStatements.find(name);

	if (it != preparedStatements.end()) {
		types = (*it).second;

		std::list<std::type_index>::iterator it2 = types.begin();
		while (it2 != types.end()) {
			if ((*it2).hash_code() == std::type_index(typeid(uint8_t)).hash_code()) {
				int arg = va_arg(args, int);
				prep_dynamic(arg, invoke);
			}

			if ((*it2).hash_code() == std::type_index(typeid(uint16_t)).hash_code()) {
				uint16_t arg = va_arg(args, int);
				prep_dynamic(arg, invoke);
			}

			if ((*it2).hash_code() == std::type_index(typeid(uint32_t)).hash_code()) {
				uint32_t arg = va_arg(args, uint32_t);
				prep_dynamic(arg, invoke);
			}

			if ((*it2).hash_code() == std::type_index(typeid(uint64_t)).hash_code()) {
				uint64_t arg = va_arg(args, uint64_t);
				prep_dynamic(arg, invoke);
			}

			if ((*it2).hash_code() == std::type_index(typeid(pqxx::binarystring)).hash_code()) {
				pqxx::binarystring arg = va_arg(args, pqxx::binarystring);
				prep_dynamic(arg, invoke);
			}

			it2++;
		}

		res = invoke.exec();

		worker.commit();
	}

	va_end(args);

	accessMutex.unlock();

	return res;
}

pqxx::result PostgresConnector::exec(std::string sql) {
	accessMutex.lock();

	pqxx::work worker(*connection);
	pqxx::result res = worker.exec(sql);

	accessMutex.unlock();

	return res;
}
