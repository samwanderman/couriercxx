/*
 * PostgresConnector.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "PostgresConnector.h"

#ifdef _WIN32
#else
#include <pqxx/binarystring.hxx>
#include <pqxx/connection>
#include <pqxx/prepared_statement.hxx>
#include <pqxx/result>
#include <pqxx/transaction>
#endif
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <exception>
#include <utility>

#include "../logger/Log.h"
#include "Value.h"

#define BUFFER_SIZE	1024

#ifdef _WIN32
#else
template<typename T>
pqxx::prepare::invocation& prep_dynamic(T value, pqxx::prepare::invocation& inv) {
	inv(value);

	return inv;
}

#endif

PostgresConnector::PostgresConnector(std::string host, uint16_t port, std::string username, std::string password, std::string dbName, std::string encoding) {
	this->host		= host;
	this->port		= port;
	this->username	= username;
	this->password	= password;
	this->dbName	= dbName;
	this->encoding	= encoding;
#ifdef _WIN32
#else
	connection		= nullptr;
#endif
}

PostgresConnector::~PostgresConnector() {
	close();
}

int PostgresConnector::open() {
	if (opened) {
		return -1;
	}
#ifdef _WIN32
#else

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
		Log::error("%s", e.what());
		return -1;
	}
#endif

	return 0;
}

int PostgresConnector::close() {
	if (!opened) {
		return -1;
	}

#ifdef _WIN32
#else
	if (connection != nullptr) {
		if (connection->is_open()) {
			connection->disconnect();
		}

		delete connection;
		connection = nullptr;
	}
#endif

	opened = false;

	return 0;
}

int PostgresConnector::reopen() {
	close();

	return open();
}

bool PostgresConnector::isOpen() {
#ifdef _WIN32
	return false;
#else
	return opened && connection->is_open();
#endif
}

int PostgresConnector::addStatement(std::string name, std::string sql, std::list<std::type_index> types) {
#ifdef _WIN32
#else
	connection->prepare(name, sql);
	preparedStatements.insert(std::pair<std::string, std::list<std::type_index>>(name, types));
#endif

	return 0;
}

int PostgresConnector::addStatement(std::string name, std::string sql) {
	std::list<std::type_index> types;

	return addStatement(name, sql, types);
}

int PostgresConnector::removeStatement(std::string name) {
#ifdef _WIN32
#else
	connection->unprepare(name);
#endif

	return preparedStatements.erase(name) > 0 ? 0 : -1;
}


#ifdef _WIN32
#else
pqxx::result PostgresConnector::execStatement(std::string name, ...) {
	accessMutex.lock();
	va_list args;
	va_start(args, name);

	pqxx::work worker(*connection);
	pqxx::prepare::invocation invoke = worker.prepared(name);
	pqxx::result res;
	res.clear();

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

			if ((*it2).hash_code() == DB::typeINT8T.hash_code()) {
				DB::Int8Value arg = va_arg(args, DB::Int8Value);
				if (arg.value != nullptr) {
					int16_t val = *arg.value;
					prep_dynamic(val, invoke);
				} else {
					prep_dynamic((const char*) nullptr, invoke);
				}
			}

			if ((*it2).hash_code() == DB::typeUINT8T.hash_code()) {
				DB::UInt8Value arg = va_arg(args, DB::UInt8Value);
				if (arg.value != nullptr) {
					uint16_t val = *arg.value;
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

			if ((*it2).hash_code() == DB::typeINT16T.hash_code()) {
				DB::Int16Value arg = va_arg(args, DB::Int16Value);
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

			if ((*it2).hash_code() == DB::typeINT32T.hash_code()) {
				DB::Int32Value arg = va_arg(args, DB::Int32Value);
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

#endif
