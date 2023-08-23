// WavConvConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Program to convolude audio files. Starting as a console app. 

//TO DO LIST
// Get set up, declare needed varaibles
//Get data from the user for those variables
//Write main loop to randomly grab samples from audio file to a new buffer
//Save said file. 
//Use read me for audiofile.h to help. Thank god for opensauce. https://github.com/adamstark/AudioFile/blob/master/AudioFile.h



#include <iostream>
#include <audiofile.h>
#include <cstdlib>
using namespace std;


//Okay dude lets get set up.
AudioFile<double> audioFile;
Audiofile<double> audioFile2;
int clipLength;
int outputLength
int loop1;
int innerloop;
int sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

int numSamples = audioFile.getNumSamplesPerChannel();
double lengthInSeconds = audioFile.getLengthInSeconds();

int numChannels = audioFile.getNumChannels();
bool isMono = audioFile.isMono();
bool isStereo = audioFile.isStereo();







//Ok dude Lets get writing the main program. Here we wanna start grabbing the users variables. 
//- start with just clip length, then maybe we can look into gain also. Which can easily vary for each pass of the loop. We need to look into RAND. Probably need c++ math library for this

int main()
{
    
    cout << "**** Audio Convolution tool. Only supports WAV/AIFF files ****";
    cin >> "Enter length of audio clip" >> clipLength;
    cin >> "Enter length of output audio file" >> outputLength;
    cout << "Audio clip length: " << clipLength;
    cout << "Output file length: " << outputLength;


    return 0;
}

















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
