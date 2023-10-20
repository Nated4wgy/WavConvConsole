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
//Set up audio file buffers one for user audio file the second for the resulting output
//later down the line would be nice to add checks to ensure the output audiobuffer is being set up correctly. Throw an error if not.
AudioFile<float> audioFile;
AudioFile<float> b;
//Set the rest of global vaeriables for user entered information and other needed for program.
int clipLength;
float outputLength;
int innerLoop;
string filePath;
string outputFile;
float gain = 0.5f; //Test variable may need later to add extra functionality to the code maybe allow the user to set a random or user defined gain for each audio snippet.

//Variables needed for the audiofile.h header. This will just make coding a little easier down the line not needing to type out the long template names. 
double sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();
double numSamples = audioFile.getNumSamplesPerChannel();
double lengthInSeconds = audioFile.getLengthInSeconds();
int numChannels = audioFile.getNumChannels();
bool isMono = audioFile.isMono();
bool isStereo = audioFile.isStereo();


//Main code starts here. This may need to change down the line as we add a UI or something along those lines

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
    cout << "Audio clip length: "  << clipLength << endl;
    cout << "Output file length: " << outputLength << endl;
    cout << "Output file gain: " << gain << endl;
    //code to define outout audio file type goes here. Need some if statements. 
    //Later we need to add code to specify the format of the output file. WAV/AIFF. Currently defaults to WAV
    //get the audio file location from the user. 
    cout << "Enter filepath of WAV/AIFF file: "; 
    cin >> filePath;
    audioFile.load(filePath);
    bool loadedOK = audioFile.load(filePath);
    //Set up the audiofile buffer here according to the info provided by audioFile header. We need the output to be the same as the input to avoid any bad bad. As we cycle from one channel, to the next.
    //If the file is say mono and we try to set up a stereo output file we are gonna get some wierdness with the main program loop
    b.setAudioBufferSize (numChannels, numSamples);
	b.setBitDepth = audioFile.getBitDepth;
	b.setSampleRate = audioFile.getSampleRate;
    audioFile.printSummary();
    cout << "Enter filepath for new file: " << endl;
    cin >> outputFile;
	
	//This code needs looking at. Seems to crash the program. might be worth returning to simpler random code. Psuedo ranomiser.
    //set up random number generator 
    //random_device rd;
    //mt19937 gen(rd());
    //Define the range for the random number, so we dont try to grab samples from outside the buffer
    //This is defined by 1 and the number of samples in the users audiofile.
    //uniform_int_distribution<> distribution(1, numSamples);
	int min = 0;
	int random_integer;
	std::random_device rd;     // Only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min,numSamples); // Guaranteed unbiased

	auto random_integer = uni(rng);
	cout << "random_integer =" random_integer << endl;
	
	
	//Need to some math here to get user vasriables into useable numbers for the code.
	//outputlength needs conversion from seconds to samples. simple. Length in seconds multiplied by samplerate of the input file.
	
	outputLength = outputLength * sampleRate;
	cout << "Output file length in samples (remove this after debug): " << endl;
	
	break;
	
	 //Start the loop. We want to here randomly access the samples in chunks of miliseconds set by the user.
    //First for loop loops until the desired output length is reached. Im hoping we dont get any wierdness at the end of the file if the output length isnt divisable by the cliplength. #
    //Maybe we can add a check for this down the line and throw an error or round it to the closest divisable. Or we can try to add code to fade out at the end of the clip 
    //Latter is much more work as we need to chnage gain over time. First is less convinient for the user but is SO much less work.
    for (int i = 0; i < outputLength; i++)
    {
        //Generate the random number here and store it so it can be changed each iteration of the loop. 
        //int randomNum = distribution(gen);
		auto random_integer = uni(rng);
        
        //Second loop here will loop until all channels are filled according to the number of channels in the user audiofile. Ensuring we dont just fill one channel with samples.
        //This also allows the next loopm to be able to know what channel it is working on each iteration
        for (int channel = 0; channel < audioFile.getNumChannels(); channel++)
        {
            //Here is the main sauce This will grab a random start sample - then grab a number of samples according to the user input. then the loop ends
            //Next iteration it will then choose a new random start point for the samples and so on. Until we have a resulting audio file of random chunks for the input file.
            //COOOOOOOL!
            for (int k = 0; k < clipLength; k++)
            b.samples[channel][i] = audioFile.samples[channel][random_integer];
        }
    }
     //Here we save that file into a WAV file. Later I plan to add the function to allow users to save to WAV or AIFF not just WAV. This shouldnt be much work at all. 
    b.save(outputFile, AudioFileFormat::Wave);

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
