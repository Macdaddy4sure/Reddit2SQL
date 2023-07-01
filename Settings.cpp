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

#include "RedditParse.h"
#include "Settings.h"

using namespace std;

void _Settings::Settings()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    string input;
    bool boolean = false;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database_submissions.c_str(), 3306, NULL, 0);

    while (!boolean)
    {
        system("cls");

        cout << endl;
        cout << "============= Settings ==============" << endl;
        cout << "| 1. Set MySQL Hostname             |" << endl;
        cout << "| 2. Set MySQL Username             |" << endl;
        cout << "| 3. Set MySQL Password             |" << endl;
        cout << "| 4. Set MySQL Database             |" << endl;
        cout << "| 5. Reddit Dump Location           |" << endl;
        cout << "-------------------------------------" << endl;
        cout << "| 0. Settings                       |" << endl;
        cout << "-------------------------------------" << endl;
        cout << endl;
        if (conn)
            cout << "MySQL Connection: True" << endl;
        else
            cout << "MySQL Connection: False" << endl;
        cout << "MySQL Hostname: " << mysql_hostname << endl;
        cout << "MySQL Username: " << mysql_username << endl;
        cout << "MySQL Password: " << mysql_password << endl;
        cout << "MySQL Database Submissions: " << mysql_database_submissions << endl;
        cout << "MySQL Database Comments: " << mysql_database_comments << endl;
        cout << "Reddit Location: " << reddit_location << endl;
        cout << endl;
        cout << "Your Selection: ";
        getline(cin, input);

        if (input == "1")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Hostname: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_hostname = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "2")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Username: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_username = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "3")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "MySQL Password: ";
                getline(cin, input);

                if (input != "")
                {
                    mysql_password = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "4")
        {
            bool boolean2 = false;

            while (!boolean2)
            {
                system("cls");

                cout << "Reddit Location: ";
                getline(cin, input);

                if (input != "")
                {
                    reddit_location = input;
                    boolean2 = true;
                }
            }
        }
        if (input == "0")
        {
            boolean = true;
        }
    }
}