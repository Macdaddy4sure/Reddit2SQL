#pragma once

/*
    Copyright(c) 2023 Tyler Crockett | Macdaddy4sure.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissionsand
    limitations under the License.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <mysql.h>
#include <curl/curl.h>

using namespace std;

class _RedditParse
{
public:
    static void Parser();
    static void RedditSubmissions();
    static void RedditComments();
    static void CreateTableSubmissions(string sub_reddit);
    static void CreateTableComments(string subreddit);
    static void QueryDatabaseSubmissions(string subreddit, string id, string author, string created_utc, string permalink, string score, string self_text, string title, string url, string is_reddit_media_domain);
    static void QueryDatabaseComments(string subreddit, string author, string created_utc, string score, string body, string ups, string downs, string link_id, string sub_reddit_parent_id, string score_hidden);
    static string FixStrings(string input);
    static string FixEmptyString(string input);
    static string FixQuotes(string input);
    static string FixSubreddit(string input);
    static string DownloadLink(string url, string title);
    static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream);
};