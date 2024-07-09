// DoubleCircular.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include "DoubleCircular.h"
using namespace std;
DoubleCircular::DoubleCircular()
{
	ifstream playlistFile;
	playlistFile.open("Playlist.txt");

	if (playlistFile.is_open())
	{
		string line;
		while (getline(playlistFile, line))
		{
			stringstream ss(line);
			string song, artist;

			getline(ss, song, ',');
			getline(ss, artist);

			NodePointer newNode = new Node(song, artist);

			if (first == nullptr)
			{
				first = newNode;
				newNode->next = newNode;
				newNode->previous = newNode;
			}
			else
			{

				NodePointer ptrLast = first->previous;
				newNode->next = first;
				newNode->previous = first;
				ptrLast->next = newNode;
				first->previous = newNode;
			}
		}
		playlistFile.close();
	}
	else
	{
		cerr << "Error opening Playlist file." << endl;
	}

}

DoubleCircular::~DoubleCircular()
{
	if (first == nullptr)
	{
		cerr << "The playlist is empty." << endl;
		exit(1);
	}
	else
	{
		NodePointer ptr = first, temp;
		do {
			temp = ptr;
			ptr = ptr->next;
			delete temp;
		} while (ptr != first);
	}
}
void DoubleCircular::addSong(const ElementType& song, const ElementType& artist)
{
	NodePointer newNode = new Node(song, artist);
	if (first == nullptr)
	{
		first = newNode;
		newNode->next = newNode;
		newNode->previous = newNode;
	}
	else
	{
		NodePointer ptrLast = first->previous;
		newNode->next = first;
		newNode->previous = ptrLast;
		ptrLast->next = newNode;
		first->previous = newNode;
	}
}
void DoubleCircular::ShufflePlaylist()
{

	if (first == nullptr || first->next == first) {
		return;
	}

	int n = 0;
	NodePointer temp = first;
	do {
		++n;
		temp = temp->next;
	} while (temp != first);

	srand(time(0));

	for (int i = n - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		NodePointer nodeI = getNodeAtIndex(i);
		NodePointer nodeJ = getNodeAtIndex(j);

		string tempSong = nodeI->song;
		nodeI->song = nodeJ->song;
		nodeJ->song = tempSong;

		string tempArtist = nodeI->artist;
		nodeI->artist = nodeJ->artist;
		nodeJ->artist = tempArtist;
	}
}
void DoubleCircular::printPlaylist() const
{
	if (first == nullptr)
	{
		cerr << "The playlist is empty." << endl;

	}
	else
	{
		NodePointer ptr = first;
		do {
			cout << ptr->song << " by " << ptr->artist << endl;
			ptr = ptr->next;

		} while (ptr != first);
	}

}
void DoubleCircular::shiftForward(const ElementType& currentSong, const ElementType& currentArtist)
{
	if (first == nullptr || first->next == first)
	{
		cout << "The playlist is empty or have on song." << endl;
		exit(1);
	}
	else
	{
		NodePointer ptr = first;
		while (ptr != nullptr)
		{
			if (ptr->song == currentSong && ptr->artist == currentArtist)
			{
				ptr = ptr->next;
				cout << "The current song is (" << ptr->song << " by " << ptr->artist << ")" << endl;
				break;
			}
			ptr = ptr->next;
		}
	}
}

void DoubleCircular::shiftBackward(const ElementType& currentSong, const ElementType& currentArtist)
{
	if (first == nullptr || first->next == first)
	{
		cout << "The playlist is empty or have on song." << endl;
		exit(1);
	}
	else
	{
		NodePointer ptr = first;
		while (ptr != nullptr)
		{
			if (ptr->song == currentSong && ptr->artist == currentArtist)
			{
				ptr = ptr->previous;
				cout << "The current song is (" << ptr->song << " by " << ptr->artist << ")" << endl;
				break;
			}
			ptr = ptr->previous;
		}
	}
}

void DoubleCircular::move(const ElementType& movedSong, const ElementType& movedArtist, const ElementType& afterSong, const ElementType& afterArtist)
{
	if (first == nullptr)
	{
		std::cerr << "The playlist is empty." << std::endl;
		return;
	}

	NodePointer current = first;
	do
	{
		if (current->song == movedSong && current->artist == movedArtist)
		{
			current->previous->next = current->next;
			current->next->previous = current->previous;
			NodePointer destination = first;
			while (destination->song != afterSong || destination->artist != afterArtist)
			{
				destination = destination->next;
				if (destination == first)
				{
					cerr << "song " << afterSong << " by " << afterArtist << " not found in the playlist." << endl;
					return;
				}
			}
			current->previous = destination;
			current->next = destination->next;
			destination->next->previous = current;
			destination->next = current;
			cout << "Song " << movedSong << " by " << movedArtist << " found in the playlist." << std::endl;
			return;
		}
		current = current->next;
	} while (current != first);
	cout << "song " << movedSong << " by " << movedArtist << "  not found in the playlist." << endl;
}


bool DoubleCircular::searchForASong(const ElementType& song, const ElementType& artist)
{
	bool found = false;
	NodePointer ptr = first;

	if (first == nullptr)
	{
		cerr << "Error: The playlist is empty." << endl;
		exit(1);
	}

	do
	{
		if (ptr->song == song && ptr->artist == artist)
		{
			found = true;
			break;
		}
		ptr = ptr->next;

	} while (ptr != first);


	if (found == false)
	{
		cout << "Song not found!" << endl;
		
	}
	else if (found == true)
	{
		cout << "Found the song!" << endl;
	}
	else
	{
		cout << "Error!" << endl;
	}

}

int DoubleCircular::numberOfSongs()
{
	int counter = 0;
	NodePointer ptr = first;
	while (ptr != nullptr) {
		counter++;
		ptr = ptr->next;
		if (ptr == first) {
			break;
		}
	}
	return counter;

}

void DoubleCircular::removeSong(const ElementType& song, const ElementType& artist)
{
	if (first == nullptr)
    {
        cout << "The playlist is empty." << endl;
        return;
    }
    
    NodePointer ptr = first;
    do
    {
        if (ptr->song == song && ptr->artist == artist)
        {
            // Only one song
            if (ptr->next == first)
            {
                delete ptr;
                first = nullptr;
            }
            else
            {
                ptr->previous->next = ptr->next;
                ptr->next->previous = ptr->previous;
                if (ptr == first)
                {
                    first = ptr->next;
                }
                NodePointer toBeRemoved = ptr;
                ptr = ptr->next;
                delete toBeRemoved;
            }
            cout << "Song (" << song << " by " << artist << ") removed from the playlist." << endl;
            return;
        }
        ptr = ptr->next;
    } while (ptr != first);

    cout << "Song " << song << " by " << artist << " not found in the playlist." << endl;

}

void DoubleCircular::exitTheProgram()
{
	cout << "Are you sure?" << endl;
	string reply;
	cin >> reply;
	if (reply == "yes")
	{
		ofstream write;
		write.open("Playlist.txt");
		if (write.is_open())
		{
			NodePointer ptr = first;
			do {
				write << ptr->song << "," << ptr->artist << "\n";
				ptr = ptr->next;

			} while (ptr != first);
			write.close();
			cout << "Playlist saved." << endl;
			exit(0);
		}
		else
		{
			cerr << "Error: opening the file." << endl;
		}
	}
	else
	{
		cout << "Error: exiting canceled" << endl;
	}
}


