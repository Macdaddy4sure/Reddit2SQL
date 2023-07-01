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

using namespace std;

class _Settings
{
public:
    static void Settings();
};

static string mysql_hostname = "localhost";
static string mysql_username = "tyler";
static string mysql_password = "Anaheim92801%";
static string mysql_database_submissions = "reddit_submissions";
static string mysql_database_comments = "reddit_comments";
static string reddit_location = "G:/Datasets/Reddit/submissions/Done/";