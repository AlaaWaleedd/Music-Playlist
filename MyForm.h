#pragma once

using namespace System;

generic <typename T>
ref class DoubleCircular
{
private:
    ref class Node
    {
    public:
        T songData;
        Node^ next;
        Node^ previous;

        Node(T songData)
            : songData(songData), next(nullptr), previous(nullptr)
        {
        }
    };

    Node^ first;

    Node^ GetNodeAtIndex(int index)
    {
        Node^ temp = first;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp;
    }

public:
    DoubleCircular();
    ~DoubleCircular();

    void AddSong(T songData);
    void RemoveSong(T songData);
    void PrintPlaylist();
    int NumberOfSongs();
    void SearchForASong(T songData);
    void ShufflePlaylist();
    void MoveSong(T movedSongData, T afterSongData);
    void ShiftForward(T currentSongData);
    void ShiftBackward(T currentSongData);
    void ExitTheProgram();
    void DisplayMenu();
};