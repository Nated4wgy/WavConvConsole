#include <iostream>
#include <AudioFile.h>
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
float outputLength;
string filePath;
string outputFile;

// main program begins here.

int main()
{
    //Gather user info for the main program vars
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
    cout << "Enter Gain level of output file (Between 0.1 > 1, 1 is full gain)"; cin >> gain;
    cout << "Audio clip length: " << clipLength << endl;
    cout << "Output file length: " << outputLength << endl;
   // cout << "Output file gain: " << gain << endl;
    //code to define outout audio file type goes here. Need some if statements. 
    //Later we need to add code to specify the format of the output file. WAV/AIFF. Currently defaults to WAV
    //get the audio file location from the user. 
    cout << "Enter filepath of WAV/AIFF file: ";
    cin >> filePath;
    a.load(filePath);
    bool loadedOK = audioFile.load(filePath);
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
    b.setAudioBufferSize(numChannels, numSamples);
    b.setBitDepth = audioFile.getBitDepth;
    b.setSampleRate = audioFile.getSampleRate;
    audioFile.printSummary();
    cout << "Enter filepath for new file: " << endl;
    cin >> outputFile;


    //Setting up random integer code
    int min = 0;
    int random_Integer;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int>uni(min, numSamples);

    auto random_Integer = uni(rng);
    //More console debug can be removed later.
    cout << "Random Sample = "; random_Integer << endl;


    //Math here to convert user variables into useable ones for samples
    outputLength = outputLength * sampleRate;
    clipLength = clipLength * 0.001;
    clipLength = clipLength * sampleRate;

    // Remove this line after debug. Only here to make sure the code is working correctly. 
    cout << "Output file length in samples (remove this after debug): ";  outputLength << endl;
    


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

    b.save(outputFile, AudioFileFormat::Wave);



}
