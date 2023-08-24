// WavConvConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Program to convolude audio files. Starting as a console app. 

//TO DO LIST
// Get set up, declare needed varaibles - DONE
//Get data from the user for those variables - DONE
//Write main loop to randomly grab samples from audio file to a new buffer - Loop set up, needs random magic.
//Save said file. - DONE
//Use read me for audiofile.h to help. Thank god for opensauce. https://github.com/adamstark/AudioFile/blob/master/AudioFile.h



#include <iostream>
#include <audiofile.h>
#include <random>
using namespace std;


//Okay dude lets get set up.
AudioFile<float> audioFile;
int clipLength;
int outputLength;
int loop1;
int innerloop;
string filePath;
string outputFile;
double sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

double numSamples = audioFile.getNumSamplesPerChannel();
double lengthInSeconds = audioFile.getLengthInSeconds();

int numChannels = audioFile.getNumChannels();
bool isMono = audioFile.isMono();
bool isStereo = audioFile.isStereo();







//Ok dude Lets get writing the main program. Here we wanna start grabbing the users variables. 
//- start with just clip length, then maybe we can look into gain also. Which can easily vary for each pass of the loop. We need to look into RAND. Probably need c++ math library for this

int main()
{
    //Gather user info for the main program, clip length, output file length
    cout << "**** Audio Convolution tool by Nated4wgy. Uses Audiofile.h from Adam Stark Github. Only supports WAV/AIFF files ****" << endl;
    cout << "https://github.com/adamstark/AudioFile/blob/master/AudioFile.h" << endl;
    cout << "                                  ;;;;;;;;;;;;;;;;;;;                                                               " << endl;
    cout << "                                  ;;;;;;;;;;;;;;;;;;;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                                  ;                 ;                                                               " << endl;
    cout << "                             ,;;;;;            ,;;;;;                                                               " << endl;
    cout << "                             ;;;;;;            ;;;;;;                                                               " << endl;
    cout << "                             `;;;;'            `;;;;'                                                               " << endl;
    cout << "\n\n\n\n\n";
    cout << "Enter audio clip length(In miliseconds): "; cin >> clipLength;
    cout << "Enter output file length(In seconds): "; cin >> outputLength;
    cout << "Audio clip length: " << clipLength << endl;
    cout << "Output file length: " << outputLength << endl;
    //get the audio file location from the user. 
    cout << "Enter filepath of WAV/AIFF file: "; 
    cin >> filePath;
    audioFile.load(filePath);
    bool loadedOK = audioFile.load(filePath);
    audioFile.printSummary();
    cout << "Enter filepath for new file: " << endl;
    cin >> outputFile;



    //set up random number generator and give it a place to live.
    //default_random_engine generator;
   // uniform_int_distribution<int> distribution(1, numSamples);
   // int randNum = distribution(generator);

    //Start the loop. We want to here randomly access the samples in chunks of miliseconds set by the user.

    float gain = 0.5f;

    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
    {


        for (int channel = 0; channel < audioFile.getNumChannels(); channel++)
        {
            audioFile.samples[channel][i] = audioFile.samples[channel][i] * gain;
        }
    }

    audioFile.save(outputFile, AudioFileFormat::Wave);

    




    

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
