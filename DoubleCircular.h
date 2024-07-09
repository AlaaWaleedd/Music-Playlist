#pragma once
#ifndef DOUBLECIRCULAR_H
#define DOUBLECIRCULAR_H
#include <iostream>
using namespace std;
typedef string ElementType;

class DoubleCircular
{
private:

    class Node {
    public:


        ElementType song;
        ElementType artist;
        Node* next;
        Node* previous;
        Node(const ElementType& song, const ElementType& artist) :song(song), artist(artist), next(0), previous(0) {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    int playlistSize;


    //Helper function
    NodePointer getNodeAtIndex(int index) {
        NodePointer temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

public:
    DoubleCircular();

    ~DoubleCircular();

    bool IsEmpty();

    void addSong(const ElementType& song, const ElementType& artist);

    void removeSong(const ElementType& song, const ElementType& artist);

    void printPlaylist() const;

    int numberOfSongs();

    bool searchForASong(const ElementType& song, const ElementType& artist);

    void ShufflePlaylist();

    void shiftForward(const ElementType& currentSong, const ElementType& currentArtist);

    void shiftBackward(const ElementType& currentSong, const ElementType& currentArtist);

    void move(const ElementType& searchedSong, const ElementType& searchedArtist, const ElementType& movedSong, const ElementType& movedrtist);

    void exitTheProgram();
};
#endif // DOUBLECIRCULAR_H

