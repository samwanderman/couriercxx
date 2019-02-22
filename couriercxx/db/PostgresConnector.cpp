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
#include <cstring>
#include <exception>
#include <utility>

#include "Value.h"

#define BUFFER_SIZE	1024

template<typename T>
pqxx::prepare::invocation& prep_dynamic(T value, pqxx::prepare::invocation& inv) {
	inv(value);
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

	try {
		char buffer[BUFFER_SIZE];
		sprintf(buffer, "host=%s port=%u user=%s password=%s dbname=%s\r\n", host.c_str(), port, username.c_str(), password.c_str(), dbName.c_str());
		connection = new pqxx::connection(buffer);
		if (!connection->is_open()) {
			close();

			return -1;
		}
		connection->set_client_encoding(encoding);

		opened = true;
	} catch (const std::exception& e) {
		return -1;
	}

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

int PostgresConnector::reopen() {
	close();
	return open();
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
	memset(&res, 0, sizeof(res));

	std::list<std::type_index> types;
	std::map<std::string, std::list<std::type_index>>::iterator it = preparedStatements.find(name);

	if (it != preparedStatements.end()) {
		types = (*it).second;

		std::list<std::type_index>::iterator it2 = types.begin();
		while (it2 != types.end()) {
			if ((*it2).hash_code() == DB::typeBool.hash_code()) {
				DB::BoolValue arg = va_arg(args, DB::BoolValue);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeString.hash_code()) {
				DB::StringValue arg = va_arg(args, DB::StringValue);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeUINT8T.hash_code()) {
				DB::UInt8Value arg = va_arg(args, DB::UInt8Value);
				uint16_t val = *arg.value;
				if (arg.value != nullptr) {
					prep_dynamic(val, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeUINT16T.hash_code()) {
				DB::UInt16Value arg = va_arg(args, DB::UInt16Value);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeUINT32T.hash_code()) {
				DB::UInt32Value arg = va_arg(args, DB::UInt32Value);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeUINT64T.hash_code()) {
				DB::UInt64Value arg = va_arg(args, DB::UInt64Value);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeINT64T.hash_code()) {
				DB::Int64Value arg = va_arg(args, DB::Int64Value);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeArray.hash_code()) {
				DB::ArrayValue arg = va_arg(args, DB::ArrayValue);
				if (arg.value != nullptr) {
					prep_dynamic(*arg.value, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			it2++;
		}

		try {
			res = invoke.exec();

			worker.commit();
		} catch (const std::exception& e) {
			va_end(args);

			accessMutex.unlock();

			throw;
		}
	}

	va_end(args);

	accessMutex.unlock();

	return res;
}

pqxx::result PostgresConnector::exec(std::string sql) {
	try {
		accessMutex.lock();

		pqxx::work worker(*connection);
		pqxx::result res = worker.exec(sql);
		worker.commit();

		accessMutex.unlock();

		return res;
	} catch (const std::exception& e) {
		accessMutex.unlock();

		throw;
	}
}
