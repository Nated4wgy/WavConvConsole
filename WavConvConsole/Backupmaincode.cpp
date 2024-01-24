#include <iostream>
#include "AudioFile.h"
#include <random>
using namespace std;

//Global variables

//Audiofile vectors
AudioFile<float> a;
AudioFile<float> b;

//variables for easy life later on - Remmeber to initilise these later on after file loading!!
double sampleRate;
int bitDepth;
double numSamples;
double lengthInS;
int numChannels;
bool isMono;
bool isStereo;

//variables for program math
float clipLength;
int outputLength;
string filePath;
string outputFile;
float outputGain;

// main program begins here.

int main()
{
    //Gather user info for the main program vars and add a little interfaceness before adding a UI API
    cout << "**** Audio Convolution tool by Nated4wgy. Uses Audiofile.h from Adam Stark Github. Only supports WAV/AIFF files ****" << endl;
    cout << "https://github.com/adamstark/AudioFile/blob/master/AudioFile.h" << endl;
    cout << "More file support is planned for later releases" << endl;
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
    cout << "Enter Gain level of output file (Between 0.1 > 1, 1 is full gain)"; cin >> outputGain;
    cout << "Audio clip length: " << clipLength << endl;
    cout << "Output file length: " << outputLength << endl;
    cout << "Output file gain: " << outputGain << endl;
    //code to define output audio file type goes here. Need some if statements. 
    //Later we need to add code to specify the format of the output file. WAV/AIFF. Currently defaults to WAV

    cout << "Enter filepath of WAV/AIFF file: "; //get the audio file location from the user. 
    cin >> filePath;
    a.load(filePath);
    bool loadedOK = a.load(filePath);
    //update variables now file is loaded.
    double sampleRate = a.getSampleRate();
    int bitDepth = a.getBitDepth();
    double numSamples = a.getNumSamplesPerChannel();
    double lengthInS = a.getLengthInSeconds();
    int numChannels = a.getNumChannels();
    bool isMono = a.isMono();
    bool isStereo = a.isStereo();

    //Set up the audiofile buffer here according to the info provided by audioFile header. 
    //At some point we need to add a check here for Mono tracks. So channels get set correctly. should be pretty easy  due to the header.
    //Will require some if/else magic. If mono then mono loop > else stereo loop. Loops will be practically identical.   
    // Need to add some math so that we can increase the buffer by the amount of one Snippet of the audio file
    //Without this we are probably running into a buffer overflow. Which explains the crashes.!
    clipLength = clipLength * 0.001; //convert milliseconds to seconds so I can get the correct amount of samples to add to the buffer. 
    //Avoiding any possible overflow situation.
    clipLength = clipLength * numSamples;
    double noOverflow = clipLength + numSamples;
    b.setAudioBufferSize(numChannels, noOverflow);
    //set audio buffer size (numsamples + clip length in samples to stop the buffer overflow crash)
    b.setBitDepth(bitDepth);
    b.setSampleRate(sampleRate);
    a.printSummary();
    cout << "Enter filepath for new file: " << endl;
    cin >> outputFile;


    //Setting up random integer code
    int min = 0;
    int random_Integer;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int>uni(min, numSamples);

    auto random_Integer = uni(rng);
    //More console debug can be removed later. useless info for the user.
    cout << "Random Sample (remove after debug) = "; random_Integer << endl;


    //Math here to convert user variables into useable ones for samples
    outputLength = outputLength * sampleRate;
    //clipLength = clipLength * 0.001; //Now doing this math earlier on. 
    //Needs to be calculated earlier in the code so I can avoid a buffer overflow in main program loops.
    //clipLength = clipLength * sampleRate; //Also doing this math earlier as I need the clipLength in samples to add to the end of buffer avoiding overflows.
    // Remove this line after debug. Only here to make sure the code is working correctly. 
    cout << "Output file length in samples (remove this after debug): ";  outputLength << endl;


    // need to add logic for gain into the main loop still. 
    //Now we can start the main loop and hope we hit gold. - Previously loops weren't iterating due to coding error. Conditional variable wasn't being properly initialised. 
    for (int i = 0; i < outputLength; i++)
    {
        //Gonna pop some console output here for debug remove after.
        cout << "Loop iteration: "; i << endl;
        cout << "outputLength: "; outputLength << endl;
        //Generate random number here as it will happen every loop
        auto random_Integer = uni(rng);

        //second loop to handle channels 
        for (int channel = 0; channel < numChannels; channel++)
        {
            //Inner loop. Random sample time
            for (int k = 0; k < clipLength; k++)
            {
                b.samples[channel][i] = a.samples[channel][random_Integer];
                random_Integer++;

            }
        }
    }
    //To make life easier for myself. instead of trying to apply gain to each seperate chunk. For now we can just do a second pass and add the gain to the overall file.
    //later on we can add it into the main loop so it can do this chunk by chunk. Using less processing power and taking less time. 
         //       for (int j = 0; j < b.getNumSamplesPerChannel(); i++)
        //   {
       //     for (int channel = 0; channel < b.getNumChannels(); channel++)
       //    {
      //      b.samples[channel][i] = b.samples[channel][i] * gain;
      //   }
     //   }

    b.save(outputFile, AudioFileFormat::Wave);



}
