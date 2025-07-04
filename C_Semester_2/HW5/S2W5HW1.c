#include <stdio.h>
#include <string.h>

typedef struct
{
	int day;
	int month;
	int year;
	int durationMinutes;
	char eventName[51];
} Event;

typedef struct
{
	char name[51];
	int startYear;
	int albums;
	char genre[51];
} Artist;

typedef struct {
	char username[51];
	int followers;
	int posts;
	int isVerified;
} SocialProfile;

void printEvent(Event e);
void printArtist(Artist a);
void printSocialProfile(SocialProfile sp);

int main()
{
	Event concert = {25, 6, 2025, 120, "Concert Of Ksb"};

	Artist artist = {"Ksb Muzic", 2022, 5, "Pop-Punk"};

	SocialProfile profile = {"Pablik", 50, 6, 1};

	printEvent(concert);
	printArtist(artist);
	printSocialProfile(profile);
	return 0;
}

void printEvent(Event e)
{
	printf("Event: %s\nDate: %02d/%02d/%04d\nWas %d Minutes long\n\n",e.eventName, e.day, e.month, e.year, e.durationMinutes);
}

void printArtist(Artist a)
{
	printf("Artist: %s\nStarting Year: %d\nNumber Of Albums: %d\nGenre: %s\n\n", a.name, a.startYear, a.albums, a.genre);
}

void printSocialProfile(SocialProfile sp) 
{
	printf("Social Profile:\nUsername: %s\nFollowers: %d\nPosts: %d\nVerified: %d\n\n",sp.username, sp.followers, sp.posts, sp.isVerified);
}