#include <iostream>			// include all neccesary header files!
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;		// standard name space!

// protos 
string getLabelType();
int getNumSongs();
long generateSongStreams(string labelType);
void streamingBreakdown(int, long[], long[], long[], long[], long[]);


// INIT ALL GLOBAL CONSTANTS
const double TIDAL = 0.01250;
const double AMAZON = 0.00402;
const double APPLEMUSIC = 0.00735;
const double SPOTIFY = 0.00437;
const double YOUTUBE = 0.00069;


int main()
{
	srand(time(0));		// seed our time!
	
	string labelType;		// variables to store our labelType and the number of songs
	int numSongs;
	
	labelType = getLabelType();		
	numSongs = getNumSongs();
	
	long tidalStreams[numSongs];		// initialize the arrays for each streaming platform with there size being dictated by the number of songs the user entered
	long amazonStreams[numSongs];
	long appleStreams[numSongs];
	long spotifyStreams[numSongs];
	long youtubeStreams[numSongs];
	
	for (int i = 0; i < numSongs; i++)		// a for loop that iterates and populates each array with a random number dependant on if the user selected a major label or an independant one
	{
		tidalStreams[i] = generateSongStreams(labelType);		// we set each arrays index to i to match the song numbers index and each time streams are generated they are assigned to i
		
		amazonStreams[i] = generateSongStreams(labelType);
		
		appleStreams[i] = generateSongStreams(labelType);
		
		spotifyStreams[i] = generateSongStreams(labelType);
		
		youtubeStreams[i] = generateSongStreams(labelType);
	}
	
	streamingBreakdown(numSongs, tidalStreams, amazonStreams, appleStreams, spotifyStreams, youtubeStreams); // calling the streaming breakdown function to display information on the streaming!
}

string getLabelType()
{
	string choice;
	cout << "Choose from one of the following Music Label Types:\n";		// prompts the user to select and enter a choice of A or B
	cout << "\tA - Independant Label\n";
	cout << "\tB - Major Label\n";
	cout << "Enter your choice (A or B): ";
	cin >> choice;			
	
	while (choice != "A" and choice != "a" and choice != "B" and choice != "b")		// The while loop validates user input 
	{
		cout << "\nERROR: INVALID MENU CHOICE. TRY AGAIN.\n";		// if the user entered a incorrect choice. The program will throw an error!
		cout << "Choose from one of the following Music Label Types:\n";
		cout << "\tA - Independant Label\n";
		cout << "\tB - Major Label\n";
		cout << "Enter your choice (A or B): ";
		cin >> choice;
	} 
	return choice;			// once the input has been validated we return the users choice!
}

int getNumSongs()		// A function that gets the number of songs a user wants to enter between 1 and 9
{
	int numSongs;
	cout << "\nHow many songs will be uploaded to the streaming platforms (Min: 1 - Max: 9)? ";
	cin >> numSongs;
	while (numSongs < 1 or numSongs > 9)		// a while loop that validates user input 
	{
		cout << "\nERROR: INVALID NUMBER OF SONGS. TRY AGAIN\n";		// if the user enters an incorrect range the program will throw out an error !
		cout << "\nHow many songs will be uploaded to the streaming platforms (Min: 1 - Max: 9)? ";
		cin >> numSongs;
	}
	return numSongs;		// After the number of songs has been validated we return it!
}

long generateSongStreams(string labelType)			// A function that generates a number dependant on the users choice of label Type !
{
	if (labelType == "A")			// if the label Type is indepentant it will return a number between 10 thousand and one million!
		return 10000 + rand() % 1000000;
	
	else 
		return 100000 + rand() % 50000000;		// Else since the only other option is the major label it will generate a number between 100 thousand and 50 million!
}

void streamingBreakdown(int numSongs, long tidalStreams[], long amazonStreams[], long appleStreams[], long spotifyStreams[], long youtubeStreams[])			
{																																				
	long platformTotal = 0, streamTotal = 0, tidalTotalStreams = 0, amazonTotalStreams = 0, appleTotalStreams = 0, spotifyTotalStreams = 0, youtubeTotalStreams = 0; 	// INIT ALL ACCUMULATORS TO ZERO
	
	cout << "\nSong #" << "\t\tTidal" << "\t\tAmazon" << "\t\tApple Music" << "\t\tSpotify" << "\t\tYouTube" << endl;	// formatting statement that prints out each respective category
	for (int i = 0; i < numSongs; i++)		// A for loop that iterates and displays the number of streams on each platform for each song.
	{
		cout << "Song #" << i + 1 << "\t\t" << tidalStreams[i] << "\t\t" << amazonStreams[i] << "\t\t" << appleStreams[i] << "\t\t\t" << spotifyStreams[i] << "\t\t" << youtubeStreams[i] << endl;
	}			// i + 1 because the index starts at 0

	cout << "\n\nStream Totals:";		// formatting cout statements 
	cout << "\n-----------------------------------\n";
	for (int i = 0; i < numSongs; i++)		// a for loop that accumulates total values and displays the total streams of a song
	{
		streamTotal = tidalStreams[i] + amazonStreams[i] + appleStreams[i] + spotifyStreams[i] + youtubeStreams[i];		// Adds the platforms streams for a song into a variable
		platformTotal += streamTotal;		// adds the streams of each song to itself as the loop iterates!
		
		tidalTotalStreams += tidalStreams[i];
		amazonTotalStreams += amazonStreams[i];
		appleTotalStreams += appleStreams[i];
		spotifyTotalStreams += spotifyStreams[i];
		youtubeTotalStreams += youtubeStreams[i];
		
		cout << "Song #" << i + 1 << "\t\tTotal Streams: " << streamTotal << endl;		// displays the song # and total streams for each song 
	}

	double tidalEarnings = tidalTotalStreams * TIDAL;				// Calculates each platforms total earnings by multiplying the total streams by each platforms respective rate!
	double amazonEarnings = amazonTotalStreams * AMAZON;
	double appleEarnings = appleTotalStreams * APPLEMUSIC;
	double spotifyEarnings = spotifyTotalStreams * SPOTIFY;
	double youtubeEarnings = youtubeTotalStreams * YOUTUBE;
	
	double totalEarnings = tidalEarnings + amazonEarnings + appleEarnings + spotifyEarnings + youtubeEarnings;	// Calculates the total earnings by adding each platforms earnings together
	
	long avgStreamsPerPlatform = platformTotal / 5;				// Calculates the avg streams per platform by dividing the platform stream total by 5 because there are 5 different platforms
	double avgEarningsPerPlatform = totalEarnings / 5;		// Calculating the avg Earnings per platform by diving the total earnings of all platforms by 5 because there are 5 platforms 

	cout << fixed << showpoint << setprecision(2);		// set precision to only allow the 2nd decimal place to show
	cout << "\n\nPlatform Totals:\t\t\tPlatform Earnings";
	cout << "\n--------------------------------------------------------------------------\n";		// formatting cout statements
	
	cout << "Tidal Streams:\t\t" << tidalTotalStreams << "\t\tTidal Earnings:" << "\t\t$" << tidalEarnings << endl; 		// Displays each respective platforms total streams and total earnings
	cout << "Amazon Music Streams:\t" << amazonTotalStreams << "\t\tAmazon Earnings:" << "\t$" << amazonEarnings << endl;
	cout << "Apple Music Streams:\t" << appleTotalStreams << "\t\tApple Music:" << "\t\t$" << appleEarnings << endl;
	cout << "Spotify Streams:\t" << spotifyTotalStreams << "\t\tSpotify Earnings:" << "\t$" << spotifyEarnings << endl;
	cout << "YouTube Streams:\t" << youtubeTotalStreams << "\t\tYoutube Earnings:" << "\t$" << youtubeEarnings << endl;
	
	cout << "--------------------------------------------------------------------------\n";
	cout << "Total Streams:\t\t" << platformTotal << "\t\tTotal Earnings:\t\t$" << totalEarnings << endl;		// Displays the entire total and earnings all platforms
	cout << "--------------------------------------------------------------------------\n";
	cout << "Avg. Streams per Platform:" << setw(13) << avgStreamsPerPlatform << endl;		// Displays the avg streams per platform 
	cout << "Avg. Earnings per Platform:" << "\t$" << avgEarningsPerPlatform << endl;	// displays avg earnings per platform
}

