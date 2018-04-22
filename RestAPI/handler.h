#pragma once
#ifndef HANDLER_H
#define HANDLER_H

#include "stdafx.h"
#include "logger.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class handler
{
public:
	handler();
	handler(utility::string_t url);
	virtual ~handler();

	http_listener m_listener;

	std::unique_ptr<logger> log;

	pplx::task<void>open() { return m_listener.open(); }
	pplx::task<void>close() { return m_listener.close(); }

//private:

	/*main path like "..\\container\\"*/
	static utility::string_t main_server_path;

	/*main path like "/container/"*/
	static utility::string_t main_server_url_path;

	/*handle GET-requests*/
	void handle_get(http_request message);
	/*handle POST-requests*/
	void handle_post(http_request message);
	/*handle DELETE-requests*/
	void handle_delete(http_request message);

	/*handle errors*/
	void handle_error(pplx::task<void>& t);

	/*handle GET-request for "/"*/
	web::json::value get_start_page();
	/*handle GET-request for "/container/[0-9]*"*/
	web::json::value get_list_container();
	/*handle GET-request for "/container\/[0-9]*"*/
	web::json::value get_container(const utility::string_t& url);
	/*handle GET-request for "\/container\/log"*/
	web::json::value get_logs();
	/*handle POST-request for "/container\/[0-9]*"*/
	web::http::status_code post_container(const utility::string_t& url);
	/*handle POST-request for "/container\/[0-9]*\/blob\/[0-9]*"*/
	web::http::status_code post_blob(const utility::string_t& cont_url, const utility::string_t& blob_url, const utility::string_t& body);
	/*handle POST-request for "/container\/[0-9]*\/merge"*/
	web::http::status_code post_merge(const utility::string_t& url, const utility::string_t& format);
	/*handle DELETE-request for "/container\/[0-9]*"*/
	web::http::status_code delete_container(const utility::string_t& url);
};

#endif // HANDLER_H

