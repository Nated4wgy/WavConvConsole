    //=======================================================================
/** @file WavConvConsole.cpp
 *  @author Nathan Wilcox
 *  @copyright Copyright (C) 2023  Nathan Wilcox
 *
 * MIT License
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
 * of the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=======================================================================




//TO DO LIST
// Get set up, declare needed varaibles - DONE
//Get data from the user for those variables - DONE
// Write code to create random number within range of 0-numSamples - DONE
//Write main loop to randomly grab samples from audio file to a new buffer - Loop set up, needs random magic. - DONE 
//Save said file. - DONE
//DEBUG MODE NOW - 
// Get creating a user interface. Choose library for this. Maybe MFC? Pretty yucky though. 


#include <iostream>
#include <audiofile.h>
#include <random>
using namespace std;


//Okay dude lets get set up.
AudioFile<float> audioFile;
int clipLength;
int outputLength;
int innerLoop;
string filePath;
string outputFile;
float gain = 0.5f;
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
    cout << "Enter Gain level of output file (Between 0.1 > 1, 1 is full gain)"; cin >> gain;
    cout << "Audio clip length: "  << clipLength << endl;
    cout << "Output file length: " << outputLength << endl;
    cout << "Output file gain: " << gain << endl;
    //Later we need to add code to specify the format of the output file. WAV/AIFF. Currently defaults to WAV
    //get the audio file location from the user. 
    cout << "Enter filepath of WAV/AIFF file: "; 
    cin >> filePath;
    audioFile.load(filePath);
    bool loadedOK = audioFile.load(filePath);
    audioFile.printSummary();
    cout << "Enter filepath for new file: " << endl;
    cin >> outputFile;

    //set up random number generator 
    random_device rd;
    mt19937 gen(rd());
    //Define the range for the random number
    uniform_int_distribution<> distribution(1, numSamples);

    //Start the loop. We want to here randomly access the samples in chunks of miliseconds set by the user.

    

    for (int i = 0; i < outputLength; i++)
    {
        //Generate the random number here and store it so it can be changed each iteration of the loop. 
        int randomNum = distribution(gen);

        for (int channel = 0; channel < audioFile.getNumChannels(); channel++)
        {
            for (innerLoop = 0; innerLoop < clipLength; innerLoop++)
            audioFile.samples[channel][randomNum] = audioFile.samples[channel][clipLength] * gain;
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
