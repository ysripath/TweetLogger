#pragma once
#include <string>
using namespace std;
class TweetData
{
private:
	static unsigned int tweetId;
	int _timestamp;
	string _hashTag;
	string _data;
	string _senderId;
	unsigned int _tweetId;
public:
	TweetData(int timestamp, string hashTag, string data, string senderId) :_timestamp(timestamp), _hashTag(hashTag), _data(data), _senderId(senderId)
	{
		_tweetId = tweetId++;
	}
	string printTweetData()
	{
		return to_string(_timestamp)+
				", " + _hashTag+
				", " + _data + 
				", " + _senderId;
	}
	const string operator + (TweetData*)
	{
		return to_string(_timestamp) +
			", " + _hashTag +
			", " + _data +
			", " + _senderId;
	}
	friend string operator + (const string &str1, const TweetData* dataPtr)
	{
		return str1 + dataPtr->printTweetData();
	}
};