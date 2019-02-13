/*
 * PostgresConnector.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_DB_POSTGRESCONNECTOR_H_
#define COURIERCXX_DB_POSTGRESCONNECTOR_H_

#include <pqxx/connection.hxx>
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <typeindex>
#include <mutex>

/**
 * Postgresql database connector
 */
class PostgresConnector {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string host - hostname
	 * \param[in] uint16_t port - port
	 * \param[in] string username - username
	 * \param[in] string password - password
	 * \param[in] string dbName - database name
	 * \param[in] string encoding - database encoding
	 */
	PostgresConnector(std::string host, uint16_t port, std::string username, std::string password, std::string dbName, std::string encoding);

	/**
	 * Destructor
	 */
	virtual ~PostgresConnector();

	/**
	 * Open database for work
	 *
	 * \return 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close database
	 *
	 * \return 0if success, -1 if error
	 */
	int close();

	/**
	 * Check if database if open
	 *
	 * \return true if open, false if closed
	 */
	bool isOpen();

	/**
	 * Add prepared statement with params
	 *
	 * \param[in] string name - name of prepared statement
	 * \param[in] string sql - sql-request to execute
	 * \param[types] - params types in order of occurance
	 *
	 * \return 0 if success, -1 if error
	 */
	int addStatement(std::string name, std::string sql, std::list<std::type_index> types);

	/**
	 * Add prepared statement
	 *
	 * \param[in] string name - name of prepared statement
	 * \param[in] string sql - sql-request to execute
	 *
	 * \return 0 if success, -1 if error
	 */
	int addStatement(std::string name, std::string sql);

	/**
	 * Execute statement
	 *
	 * \param[in] string name - name of statement to execute
	 *
	 * \return pqxx result
	 */
	pqxx::result execStatement(std::string name, ...);

	/**
	 * Execucte sql-request
	 *
	 * \param[in] string sql - string to execute
	 *
	 * \return pqxx result
	 */
	pqxx::result exec(std::string sql);

	/**
	 * Clear caches for requests - needed when field type has changed during work
	 *
	 * \return int 0 if success, -1 if error
	 */
	int clearCaches();

private:
	pqxx::connection *connection = nullptr;
	std::map<std::string, std::list<std::type_index>> preparedStatements;
	std::mutex accessMutex;

	std::string host = "";
	uint16_t port = 0;
	std::string username = "";
	std::string password = "";
	std::string dbName = "";
	std::string encoding = "";

	bool opened = false;
};

#endif /* COURIERCXX_DB_POSTGRESCONNECTOR_H_ */
