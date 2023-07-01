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
using namespace filesystem;

int main()
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
        cout << "============= Main Menu =============" << endl;
        cout << "| 1. Create Tables for SubReddits   |" << endl;
        cout << "| 2. Upload Reddit Submissions      |" << endl;
        cout << "| 3. Upload Reddit Comments         |" << endl;
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
            _RedditParse::Parser();
        }
        if (input == "2")
        {
            _RedditParse::RedditSubmissions();
        }
        if (input == "3")
        {
            _RedditParse::RedditComments();
        }
        if (input == "0")
        {
            _Settings::Settings();
        }
    }
}

void _RedditParse::Parser()
{
	string temp_path;
	string input;
	int count = 0;
	long progress = 0;
	bool bool_sub_reddit = false;
	bool bool_sub_reddit_name_prefix = false;
	int sub_reddit_count = 100;
	bool sub_reddit_test = false;
	bool sub_reddit_prefix_text = false;
	string sub_reddit;
	string sub_reddit_name_prefix;
	string temp;

	fstream file;

	// Progress
	//long count = CountFiles();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (auto& q : directory_iterator(reddit_location.c_str()))
	{
		temp_path = q.path().string();
		cout << "Filename: " << temp_path << endl;

		file.open(temp_path.c_str());

		if (file.is_open())
		{
			// Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
			while (getline(file, input))
			{
				//system("cls");
				/*cout << input << endl;*/

				//cout << "Progress: " << progress << "/" << count << endl;
				//cout << "Filename: " << temp_path << endl;
				
				bool_sub_reddit = false;
				sub_reddit.clear();

				for (int x = 0; x <= input.length(); x++)
				{
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'u' && input[x + 3] == 'b' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == 'd' && input[x + 7] == 'd' && input[x + 8] == 'i' && input[x + 9] == 't' && input[x + 10] == '\"' && input[x + 11] == ':')
					{
						for (int y = x + 13; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								//cout << input[y];
								sub_reddit += input[y];
							}
							else
							{
								break;
							}
						}
						break;
					}
				}

				temp = "`/r/";
				temp += sub_reddit;
				temp += "`";
				sub_reddit = temp;
				temp.clear();

				_RedditParse::CreateTableSubmissions(sub_reddit);
			}
		}
		file.close();
		progress++;
	}
}

void _RedditParse::RedditSubmissions()
{
	string temp_path;
	string input;
	int count = 0;
	long progress = 0;
	int sub_reddit_count = 0;

	bool bool_id = false;
	bool bool_author = false;
	bool bool_permalink = false;
	bool bool_score = false;
	bool bool_sub_reddit = false;
	bool bool_sub_reddit_name_prefix = false;
	bool bool_title = false;
	bool bool_url = false;
	bool bool_is_reddit_media_domain = false;
	bool sub_reddit_prefix_text = false;
	bool sub_reddit_test = false;

	string id;
	string author;
	string created_utc;
	string permalink;
	string score;
	string subreddit;
	string sub_reddit_name_prefix;
	string self_text;
	string title;
	string url;
	string is_reddit_media_domain;
	string temp;

	fstream file;

	// Progress
	//long count = CountFiles();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (auto& q : directory_iterator(reddit_location.c_str()))
	{
		temp_path = q.path().string();

		file.open(temp_path.c_str());

		if (file.is_open())
		{
			//cout << "TITLE: " << title << endl;
			cout << "Progress: " << progress << "/" << count << endl;

			// Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
			while (getline(file, input))
			{
				bool_author = false;
				bool_permalink = false;
				bool_score = false;
				bool_sub_reddit = false;
				bool_title = false;
				bool_url = false;
				bool_is_reddit_media_domain = false;
				id.clear();
				author.clear();
				self_text.clear();
				permalink.clear();
				score.clear();
				subreddit.clear();
				title.clear();
				created_utc.clear();
				url.clear();
				is_reddit_media_domain.clear();

				for (int x = 0; x <= input.length(); x++)
				{
					if (input[x] == '\"' && input[x + 1] == 'i' && input[x + 2] == 'd' && input[x + 3] == '\"' && input[x + 4] == ':')
					{
						for (int y = x + 6; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								id += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'a' && input[x + 2] == 'u' && input[x + 3] == 't' && input[x + 4] == 'h' && input[x + 5] == 'o' && input[x + 6] == 'r' && input[x + 7] == '\"' && input[x + 8] == ':')
					{
						for (int y = x + 10; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								author += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'c' && input[x + 2] == 'r' && input[x + 3] == 'e' && input[x + 4] == 'a' && input[x + 5] == 't' && input[x + 6] == 'e' && input[x + 7] == 'd' && input[x + 8] == '_' && input[x + 9] == 'u' && input[x + 10] == 't' && input[x + 11] == 'c' && input[x + 12] == '\"' && input[x + 13] == ':')
					{
						for (int y = x + 15; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								created_utc += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'p' && input[x + 2] == 'e' && input[x + 3] == 'r' && input[x + 4] == 'm' && input[x + 5] == 'a' && input[x + 6] == 'l' && input[x + 7] == 'i' && input[x + 8] == 'n' && input[x + 9] == 'k' && input[x + 10] == '\"' && input[x + 11] == ':')
					{
						for (int y = x + 13; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								permalink += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'c' && input[x + 3] == 'o' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == '\"' && input[x + 7] == ':')
					{
						for (int y = x + 9; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								score += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'e' && input[x + 3] == 'l' && input[x + 4] == 'f' && input[x + 5] == 't' && input[x + 6] == 'e' && input[x + 7] == 'x' && input[x + 8] == 't' && input[x + 9] == '\"' && input[x + 10] == ':')
					{
						for (int y = x + 12; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								self_text += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'u' && input[x + 3] == 'b' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == 'd' && input[x + 7] == 'd' && input[x + 8] == 'i' && input[x + 9] == 't' && input[x + 10] == '\"' && input[x + 11] == ':')
					{
						for (int y = x + 13; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								subreddit += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 't' && input[x + 2] == 'i' && input[x + 3] == 't' && input[x + 4] == 'l' && input[x + 5] == 'e' && input[x + 6] == '\"' && input[x + 7] == ':')
					{
						for (int y = x + 9; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								title += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'u' && input[x + 2] == 'r' && input[x + 3] == 'l' && input[x + 4] == '\"' && input[x + 5] == ':')
					{
						for (int y = x + 7; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								url += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'i' && input[x + 2] == 's' && input[x + 3] == '_' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == 'd' && input[x + 7] == 'd' && input[x + 8] == 'i' && input[x + 9] == 't' && input[x + 10] == '_' && input[x + 11] == 'm' && input[x + 12] == 'e' && input[x + 13] == 'd' && input[x + 14] == 'i' && input[x + 15] == 'a' && input[x + 16] == '_' && input[x + 17] == 'd' && input[x + 18] == 'o' && input[x + 19] == 'm' && input[x + 20] == 'a' && input[x + 21] == 'i' && input[x + 22] == 'n' && input[x + 23] == '\"' && input[x + 24] == ':')
					{
						for (int y = x + 26; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								is_reddit_media_domain += input[y];
							}
							else
							{
								break;
							}
						}
					}
				}

				system("cls");

				subreddit = _RedditParse::FixStrings(subreddit);
				//cout << "subreddit: " << subreddit << endl;
				subreddit = _RedditParse::FixEmptyString(subreddit);
				//cout << "subreddit: " << subreddit << endl;
				subreddit = _RedditParse::FixQuotes(subreddit);
				//cout << "subreddit: " << subreddit << endl;
				subreddit = _RedditParse::FixSubreddit(subreddit);
				//cout << "subreddit: " << subreddit << endl;
				title = _RedditParse::FixStrings(title);
				title = _RedditParse::FixEmptyString(title);
				title = _RedditParse::FixQuotes(title);
				author = _RedditParse::FixStrings(author);
				author = _RedditParse::FixEmptyString(author);
				author = _RedditParse::FixQuotes(author);
				id = _RedditParse::FixStrings(id);
				id = _RedditParse::FixEmptyString(id);
				id = _RedditParse::FixQuotes(id);
				created_utc = _RedditParse::FixStrings(created_utc);
				created_utc = _RedditParse::FixEmptyString(created_utc);
				created_utc = _RedditParse::FixQuotes(created_utc);
				created_utc = _RedditParse::FixStrings(created_utc);
				created_utc = _RedditParse::FixEmptyString(created_utc);
				created_utc = _RedditParse::FixQuotes(created_utc);
				permalink = _RedditParse::FixStrings(permalink);
				permalink = _RedditParse::FixEmptyString(permalink);
				permalink = _RedditParse::FixQuotes(permalink);
				created_utc = _RedditParse::FixStrings(created_utc);
				created_utc = _RedditParse::FixEmptyString(created_utc);
				created_utc = _RedditParse::FixQuotes(created_utc);
				score = _RedditParse::FixStrings(score);
				score = _RedditParse::FixEmptyString(score);
				score = _RedditParse::FixQuotes(score);
				self_text = _RedditParse::FixStrings(self_text);
				self_text = _RedditParse::FixEmptyString(self_text);
				self_text = _RedditParse::FixQuotes(self_text);
				url = _RedditParse::FixStrings(url);
				url = _RedditParse::FixEmptyString(url);
				url = _RedditParse::FixQuotes(url);
				is_reddit_media_domain = _RedditParse::FixStrings(is_reddit_media_domain);
				is_reddit_media_domain = _RedditParse::FixEmptyString(is_reddit_media_domain);
				is_reddit_media_domain = _RedditParse::FixQuotes(is_reddit_media_domain);

				//string html_filename = _RedditParse::DownloadLink(url, id);

				cout << "subreddit: " << subreddit << endl;
				cout << "title: " << title << endl;
				cout << "author: " << author << endl;
				cout << "id: " << id << endl;
				cout << "created_utc: " << created_utc << endl;
				cout << "permalink: " << permalink << endl;
				cout << "score: " << score << endl;
				cout << "self_text: " << self_text << endl;
				cout << "url: " << url << endl;
				cout << "is_reddit_media_domain: " << is_reddit_media_domain << endl;
				//cout << "HTML Filename: " << html_filename << endl;

				_RedditParse::CreateTableSubmissions(subreddit);
				_RedditParse::QueryDatabaseSubmissions(subreddit, id, author, created_utc, permalink, score, self_text, title, url, is_reddit_media_domain);
			}

			if (progress >= 0)
			{

			}
		}
		file.close();
		progress++;
	}
}

void _RedditParse::RedditComments()
{
	string temp_path;
	string input;
	int count = 0;
	long progress = 0;
	int sub_reddit_count = 0;

	bool bool_author = false;
	bool bool_score = false;
	bool bool_subreddit = false;
	bool bool_body = false;
	bool bool_created_utc = false;
	bool bool_ups = false;
	bool bool_downs = false;
	bool bool_link_id = false;
	bool bool_sub_reddit_parent_id = false;
	bool bool_score_hidden = false;

	string author;
	string created_utc;
	string score;
	string subreddit;
	string body;
	string ups;
	string downs;
	string link_id;
	string sub_reddit_parent_id;
	string score_hidden;
	string temp;

	fstream file;

	// Progress
	//long count = CountFiles();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (auto& q : directory_iterator(reddit_location.c_str()))
	{
		temp_path = q.path().string();

		file.open(temp_path.c_str());

		if (file.is_open())
		{
			//cout << "TITLE: " << title << endl;
			cout << "Progress: " << progress << "/" << count << endl;

			// Because there is a summary before any of the headings, we need to check if a heading has been found. If the heading has not been found, copy the 
			while (getline(file, input))
			{
				bool_author = false;
				bool_score = false;
				bool_subreddit = false;
				ups.clear();
				downs.clear();
				sub_reddit_parent_id.clear();
				score_hidden.clear();
				link_id.clear();
				created_utc.clear();
				author.clear();
				body.clear();
				score.clear();
				subreddit.clear();

				for (int x = 0; x <= input.length(); x++)
				{
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'u' && input[x + 3] == 'b' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == 'd' && input[x + 7] == 'd' && input[x + 8] == 'i' && input[x + 9] == 't' && input[x + 10] == '\"' && input[x + 11] == ':')
					{
						for (int y = x + 13; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								subreddit += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'u' && input[x + 2] == 'p' && input[x + 3] == 's' && input[x + 4] == '\"' && input[x + 5] == ':')
					{
						for (int y = x + 7; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								ups += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == '\"' && input[x + 2] == 's' && input[x + 3] == 'u' && input[x + 4] == 'b' && input[x + 5] == 'r' && input[x + 6] == 'e' && input[x + 7] == 'd' && input[x + 8] == 'd' && input[x + 9] == 'i' && input[x + 10] == 't' && input[x + 11] == '\"' && input[x + 12] == ':' && input[x + 13] == 'p' && input[x + 14] == 'a' && input[x + 15] == 'r' && input[x + 16] == 'e' && input[x + 17] == 'n' && input[x + 18] == 't' && input[x + 19] == '_' && input[x + 20] == 'i' && input[x + 21] == 'd' && input[x + 22] == '\"' && input[x + 23] == ':')
					{
						for (int y = x + 25; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								sub_reddit_parent_id += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'c' && input[x + 3] == 'o' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == '_' && input[x + 7] == 'h' && input[x + 8] == 'i' && input[x + 9] == 'd' && input[x + 10] == 'd' && input[x + 11] == 'e' && input[x + 12] == 'n' && input[x + 13] == '\"' && input[x + 14] == ':')
					{
						for (int y = x + 16; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								score_hidden += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'l' && input[x + 2] == 'i' && input[x + 3] == 'n' && input[x + 4] == 'k' && input[x + 5] == '_' && input[x + 6] == 'i' && input[x + 7] == 'd' && input[x + 8] == '\"' && input[x + 9] == ':')
					{
						for (int y = x + 11; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								link_id += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'c' && input[x + 2] == 'r' && input[x + 3] == 'e' && input[x + 4] == 'a' && input[x + 5] == 't' && input[x + 6] == 'e' && input[x + 7] == 'd' && input[x + 8] == '_' && input[x + 9] == 'u' && input[x + 10] == 't' && input[x + 11] == 'c' && input[x + 12] == '\"' && input[x + 13] == ':')
					{
						for (int y = x + 15; y <= input.length(); y++)
						{
							if (input[y] != ',')
							{
								created_utc += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'd' && input[x + 2] == 'o' && input[x + 3] == 'w' && input[x + 4] == 'n' && input[x + 5] == 's' && input[x + 6] == '\"' && input[x + 7] == ':')
					{
						for (int y = x + 9; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								downs += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 's' && input[x + 2] == 'c' && input[x + 3] == 'o' && input[x + 4] == 'r' && input[x + 5] == 'e' && input[x + 6] == '\"' && input[x + 7] == ':')
					{
						for (int y = x + 9; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								score += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'a' && input[x + 2] == 'u' && input[x + 3] == 't' && input[x + 4] == 'h' && input[x + 5] == 'o' && input[x + 6] == 'r' && input[x + 7] == '\"' && input[x + 8] == ':')
					{
						for (int y = x + 10; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								author += input[y];
							}
							else
							{
								break;
							}
						}
					}
					if (input[x] == '\"' && input[x + 1] == 'b' && input[x + 2] == 'o' && input[x + 3] == 'd' && input[x + 4] == 'y' && input[x + 5] == '\"' && input[x + 6] == ':')
					{
						for (int y = x + 8; y <= input.length(); y++)
						{
							if (input[y] != '\"')
							{
								body += input[y];
							}
							else
							{
								break;
							}
						}
					}
				}

				_RedditParse::QueryDatabaseComments(subreddit, author, created_utc, score, body, ups, downs, link_id, sub_reddit_parent_id, score_hidden);
			}

			if (progress >= 0)
			{

			}
		}
		file.close();
		progress++;
	}
}

string _RedditParse::DownloadLink(string url, string id)
{
	CURL* curl_handle;
	id += ".html";
	const char* pagefilename = id.c_str();
	FILE* pagefile;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();
	/* set URL to get here */
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	/* Switch on full protocol/debug output while testing */
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L); 
	/* disable progress meter, set to 0L to enable it */
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
	/* open the file */
	pagefile = fopen(pagefilename, "wb");

	if (pagefile)
	{
		/* write the page body to this file handle */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
		/* get it! */
		curl_easy_perform(curl_handle);
		/* close the header file */
		fclose(pagefile);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();

	for (auto& p : directory_iterator(current_path()))
	{
		string temp_path = p.path().string();

		if (p.path().filename() == pagefilename)
		{
			string temp_path2 = reddit_location;
			temp_path2 += "reddit_html/";
			temp_path2 += pagefilename;
			rename(temp_path, temp_path2);
			return temp_path2;
		}
	}

	return "NULL";
}

void _RedditParse::QueryDatabaseSubmissions(string subreddit, string id, string author, string created_utc, string permalink, string score, string self_text, string title, string url, string is_reddit_media_domain)
{
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;
	string sql1;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database_submissions.c_str(), 3306, NULL, 0);

	if (conn)
	{
		sql1 = "INSERT INTO `";
		sql1 += subreddit.c_str();
		sql1 += "`(id, title, author, created_utc, permalink, score, sub_reddit, url, self_text, is_reddit_media_domain) VALUES(\"";
		sql1 += id.c_str();
		sql1 += "\", \"";
		sql1 += title.c_str();
		sql1 += "\", \"";
		sql1 += author.c_str();
		sql1 += "\", \"";
		sql1 += created_utc.c_str();
		sql1 += "\", \"";
		sql1 += permalink.c_str();
		sql1 += "\", \"";
		sql1 += score.c_str();
		sql1 += "\", \"";
		sql1 += subreddit.c_str();
		sql1 += "\", \"";
		sql1 += url.c_str();
		sql1 += "\", \"";
		sql1 += self_text.c_str();
		sql1 += "\", \"";
		sql1 += is_reddit_media_domain.c_str();
		sql1 += "\");";
		//cout << "SQL1: " << sql1 << endl;
		mysql_query(conn, sql1.c_str());
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
	}
}

void _RedditParse::QueryDatabaseComments(string subreddit, string author, string created_utc, string score, string body, string ups, string downs, string link_id, string sub_reddit_parent_id, string score_hidden)
{
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;
	string sql1;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database_submissions.c_str(), 3306, NULL, 0);

	if (conn)
	{
		sql1 = "INSERT INTO `";
		sql1 += subreddit.c_str();
		sql1 += "`(author, created_utc, score, subreddit, body, ups, downs, link_id, sub_reddit_parent_id, score_hidden) VALUES(\"";
		sql1 += author.c_str();
		sql1 += "\", \"";
		sql1 += created_utc.c_str();
		sql1 += "\", \"";
		sql1 += score.c_str();
		sql1 += "\", \"";
		sql1 += subreddit.c_str();
		sql1 += "\", \"";
		sql1 += body.c_str();
		sql1 += "\", \"";
		sql1 += ups.c_str();
		sql1 += "\", \"";
		sql1 += downs.c_str();
		sql1 += "\", \"";
		sql1 += link_id.c_str();
		sql1 += "\", \"";
		sql1 += sub_reddit_parent_id.c_str();
		sql1 += "\", \"";
		sql1 += score_hidden.c_str();
		sql1 += "\");";
		//cout << "SQL1: " << sql1 << endl;
		mysql_query(conn, sql1.c_str());
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
	}
}

void _RedditParse::CreateTableSubmissions(string sub_reddit)
{
    MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;
	string sql1;
    string input;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database_submissions.c_str(), 3306, NULL, 0);

    if (conn)
    {
		sql1 = "CREATE TABLE `";
		sql1 += sub_reddit.c_str();
		sql1 += "`(id TEXT, title TEXT, author TEXT, created_utc TEXT, permalink TEXT, score TEXT, sub_reddit TEXT, url TEXT, self_text TEXT, is_reddit_media_domain TEXT);";
		//cout << "subreddit: " << sub_reddit << endl;
        /*cout << "SQL: " << sql1 << endl;*/
        mysql_query(conn, sql1.c_str());
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
    }
    else
    {
        cout << "Could not connect to MySQL Server..." << endl;
    }
}

void _RedditParse::CreateTableComments(string sub_reddit)
{
	MYSQL* conn;
	string input;
	string query;
	ostringstream strstr;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, mysql_hostname.c_str(), mysql_username.c_str(), mysql_password.c_str(), mysql_database_comments.c_str(), 3306, NULL, 0);

	if (conn)
	{
		strstr << "CREATE TABLE IF NOT EXISTS `" << sub_reddit.c_str() << "`(author TEXT, created_utc TEXT, score TEXT, subreddit TEXT, body TEXT, ups TEXT, downs TEXT, link_id TEXT, sub_reddit_parent_id TEXT, sore_hidden TEXT);";
		query = strstr.str();
		cout << "SQL: " << query << endl;
		mysql_query(conn, query.c_str());
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
	}
	else
	{
		cout << "Could not connect to MySQL Server..." << endl;
	}
}

string _RedditParse::FixStrings(string input)
{
	string temp;

	for (int x = 0; x <= input.length(); x++)
	{
		if (x == 0)
		{
			if (input[x] == '\\')
			{
				// lol
			}
			else
				temp = input[x];
		}
		else
		{
			if (input[x] == '\\')
			{
				//lol
			}
			else
				temp += input[x];
		}
	}

	return temp;
}

string _RedditParse::FixEmptyString(string input)
{
	if (input == "")
		return "NULL";
	if (input[0] == ',')
		return "NULL";
	else
		return input;
}

string _RedditParse::FixQuotes(string input)
{
	string temp;

	for (int x = 0; x <= input.length(); x++)
	{
		if (x == 0)
		{
			temp = input[x];
		}
		else
		{
			if (input[x] == '\"')
			{
				temp += '\'';
			}
			else
			{
				temp += input[x];
			}
		}
	}

	return temp;
}

string _RedditParse::FixSubreddit(string input)
{
	string temp;

	for (int x = 0; x <= input.length(); x++)
	{
		if (x == 0)
		{
			temp = "/r/";
			temp += input[x];
		}
		else
		{
			temp += input[x];
		}
	}

	return temp;
}

size_t _RedditParse::write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}