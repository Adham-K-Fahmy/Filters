#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

void openPicture();
void savePicture();
void pictureFilter();
void blackWhite();
void invert();
void _merge();
void flip();
void _rotate();
void darkenLighten();
void detectEdges();
void enlarge();
void shrink();
void mirror();
void shuffle();
void blur();

unsigned char image[256][256];


int main()
{
    cout << "Please enter file name of the image to process: "<< endl;
    openPicture();
    while(true){
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << "1- Black & White Filter" << endl;
        cout << "2- Invert Filter" << endl;
        cout << "3- Merge Filter" << endl;
        cout << "4- Flip Image" << endl;
        cout << "5- Rotate Image" << endl;
        cout << "6- Darken and Lighten Image" << endl;
        cout << "7- Detect Image Edges" << endl;
        cout << "8- Enlarge Image" << endl;
        cout << "9- Shrink Image" << endl;
        cout << "a- Mirror 1/2 Image" << endl;
        cout << "b- Shuffle Image" << endl;
        cout << "c- Blur Image" << endl;
        cout << "s- Save the image to a file" << endl;
        cout << "0- Exit" << endl;
        string userChoice;
        cin >> userChoice;
        if(userChoice == "1"){
            blackWhite();
        }
        else if(userChoice == "2"){
            invert();
        }
        else if(userChoice == "3"){
            _merge();
        }
        else if(userChoice == "4"){
            flip();
        }
        else if(userChoice == "5"){
            int choice;
            cout << "plaese enter your choice 90 or 180 or 270 : \n";
            cin >> choice;
            if (choice == 90)
            {
                _rotate();
            }

	        if (choice == 180)
            {
	            _rotate();
	            _rotate();
            }
            if (choice == 270)
            {
	            _rotate();
	            _rotate();
	            _rotate();
            }
        }
        else if(userChoice == "6"){
            darkenLighten();
        }
        else if(userChoice == "7"){
            detectEdges();
        }
        else if(userChoice == "8"){
            enlarge();
        }
        else if(userChoice == "9"){
            shrink();
        }
        else if(userChoice == "a"){
            mirror();
        }
        else if(userChoice == "b"){
            shuffle();
        }
        else if(userChoice == "c"){
            blur();
        }
        else if(userChoice == "s"){
            savePicture();
        }
        else if(userChoice == "0"){
            break;
        }
    }
}
void openPicture()
{
	char imageName[100];
	cin >> imageName;
	strcat(imageName, ".bmp");
	readGSBMP(imageName, image);
}
void savePicture()
{
	char imageName[100];
	cout << "Please enter the filtered photo name : ";
	cin >> imageName;
	strcat(imageName, ".bmp");
	writeGSBMP(imageName, image);
}
void blackWhite(){
    long long average = 0;
    for(int x = 0; x<SIZE; x++){
        for(int y = 0; y<SIZE; y++){
            average += image[x][y];
        }
    }
    average /= (SIZE*SIZE);
    for(int x = 0; x<SIZE; x++){
        for(int y = 0; y<SIZE; y++){
            if(image[x][y] > average){
                image[x][y] = 255;
            }
            else{
                image[x][y] = 0;
            }
        }
    }
}
void invert(){
    for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (image[i][j] == 0)
			{
				image[i][j] = 255;
			}
			else if (image[i][j] == 255)
			{
				image[i][j] = 0;
			}
			else
			{
				image[i][j] = 255 - image[i][j];
			}
		}
	}

}
void _merge(){

}
void flip(){
    cout << "please choose how to flip the image\n1- horizontally\n2- vertically\n";
    int choose;
    cin >> choose;
    if(choose == 1){
        int temp=0;
        for(int x = 0; x<SIZE; x++){
            for(int y = 0; y<SIZE/2; y++){
                temp = image[x][y];
                image[x][y] = image[x][255-y];
                image[x][255-y] = temp;
            }
        }
    }
    else{
        int temp=0;
        for(int x = 0; x<SIZE/2; x++){
            for(int y = 0; y<SIZE; y++){
                temp = image[x][y];
                image[x][y] = image[255-x][y];
                image[255-x][y] = temp;
            }
        }
    }
}
void _rotate(){
    unsigned char newImage[256][256];
    for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
		    newImage[i][j] = image[255-j][i];
		}
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
		    image[i][j] = newImage[i][j];
		}
	}


}
void darkenLighten(){

}
void detectEdges(){
    for(int x = 0; x < SIZE; x++){
        for(int y = 0; y < SIZE; y++){
            if(abs(image[x][y]-image[x][y+1]) > 35 || abs(image[x][y]-image[x+1][y]) > 35){
                image[x][y] = 0;
            }
            else{
                image[x][y] = 255;
            }
        }
    }
}
void enlarge(){
    unsigned char firstQuarter[127][127];
    unsigned char secondQuarter[127][127];
    unsigned char thirdQuarter[127][127];
    unsigned char fourthQuarter[127][127];
    int userChoice;
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    cin >> userChoice;

    if (userChoice == 1)
    {
        for (int i = 0; i < 127; i++)
        {
            for (int j = 0; j < 127; j++)
            {
                firstQuarter[i][j] = image[i][j];
            }
        }
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[2*i][2*j] = firstQuarter[i][j];
            }
        }
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        for (int i = 1 ; i < 256 ; i+=2)
        {
            for (int j = 0 ; j < 256 ; j++)
            {
                image[i][j] = image[i-1][j];
            }
        }

    }


    if (userChoice == 2)
    {
        for (int i = 0; i < 127; i++)
        {
            for (int j = 127; j < 256; j++)
            {
                secondQuarter[i][j-127] = image[i][j];
            }
        }
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[2*i][2*j] = secondQuarter[i][j];
            }
        }
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        for (int i = 1 ; i < 256 ; i+=2)
        {
            for (int j = 0 ; j < 256 ; j++)
            {
                image[i][j] = image[i-1][j];
            }
        }

    }

    if (userChoice == 3)
    {
        for (int i = 127; i < 256; i++)
        {
            for (int j = 0; j < 127; j++)
            {
                thirdQuarter[i-127][j] = image[i][j];
            }
        }
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[2*i][2*j] = thirdQuarter[i][j];
            }
        }
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        for (int i = 1 ; i < 256 ; i+=2)
        {
            for (int j = 0 ; j < 256 ; j++)
            {
                image[i][j] = image[i-1][j];
            }
        }

    }

    if (userChoice == 4)
    {
        for (int i = 127; i < 256; i++)
        {
            for (int j = 127; j < 256; j++)
            {
                fourthQuarter[i-127][j-127] = image[i][j];
            }
        }
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[2*i][2*j] = fourthQuarter[i][j];
            }
        }
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        for (int i = 1 ; i < 256 ; i+=2)
        {
            for (int j = 0 ; j < 256 ; j++)
            {
                image[i][j] = image[i-1][j];
            }
        }

    }

}
void shrink(){

}
void mirror(){
    int startRowPixel;
    int endRowPixel;
    int startColumnPixel;
    int endColumnPixel;
    int a;
    cout << "1- right \n2- left \n3- down \n4- up" << endl;
    cin >> a;
    if(a == 1){
        startRowPixel = 0;
        endRowPixel = SIZE;
        startColumnPixel = 0;
        endColumnPixel = 127;
    }
    else if(a == 2){
        startRowPixel = 0;
        endRowPixel = SIZE;
        startColumnPixel = 127;
        endColumnPixel = SIZE;
    }
    else if(a == 3){
        startRowPixel = 0;
        endRowPixel = 127;
        startColumnPixel = 0;
        endColumnPixel = SIZE;
    }
    else if(a == 4){
        startRowPixel = 127;
        endRowPixel = SIZE;
        startColumnPixel = 0;
        endColumnPixel = SIZE;
    }
    else{
        return mirror();
    }
    for(int x = startRowPixel; x<endRowPixel; x++){
        for(int y = startColumnPixel; y<endColumnPixel; y++){
            if(startRowPixel == 0 && endRowPixel == SIZE){
                image[x][y] = image[x][255-y];
            }
            else{
                image[x][y] = image[255-x][y];
            }
        }
    }
}
void shuffle(){
    unsigned char firstQuarter[127][127];
    unsigned char secondQuarter[127][127];
    unsigned char thirdQuarter[127][127];
    unsigned char fourthQuarter[127][127];
    int qrt1 , qrt2 , qrt3 , qrt4;
    cout << "New order of quarters ?";
    cin >> qrt1 >> qrt2 >> qrt3 >> qrt4;



    for (int i = 0; i < 127; i++)
    {
        for (int j = 0; j < 127; j++)
        {
            firstQuarter[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < 127; i++)
    {
        for (int j = 127; j < 256; j++)
        {
            secondQuarter[i][j-127] = image[i][j];
        }
    }

    for (int i = 127; i < 256; i++)
    {
        for (int j = 0; j < 127; j++)
        {
            thirdQuarter[i-127][j] = image[i][j];
        }
    }

    for (int i = 127; i < 256; i++)
    {
        for (int j = 127; j < 256; j++)
        {
            fourthQuarter[i-127][j-127] = image[i][j];
        }
    }


    if (qrt1 == 1)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = firstQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 2)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = secondQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 3)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = thirdQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 4)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = fourthQuarter[i][j];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }


    if (qrt2 == 1)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = firstQuarter[i][j-127];
            }
        }
    }

    else if (qrt2 == 2)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = secondQuarter[i][j-127];
            }
        }
    }

    else if (qrt2 == 3)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = thirdQuarter[i][j-127];
            }
        }
    }

    else if (qrt2 == 4)
    {
        for (int i = 0 ; i < 127 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = fourthQuarter[i][j-127];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }

    if (qrt3 == 1)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = firstQuarter[i-127][j];
            }
        }
    }

    else if (qrt3 == 2)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = secondQuarter[i-127][j];
            }
        }
    }

    else if (qrt3 == 3)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = thirdQuarter[i-127][j];
            }
        }
    }

    else if (qrt3 == 4)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 127 ; j++)
            {
                image[i][j] = fourthQuarter[i-127][j];
            }
        }
    }
    else
    {
        cout << "not valid input";
    }

    if (qrt4 == 1)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = firstQuarter[i-127][j-127];
            }
        }
    }

    else if (qrt4 == 2)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = secondQuarter[i-127][j-127];
            }
        }
    }

    else if (qrt4 == 3)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = thirdQuarter[i-127][j-127];
            }
        }
    }

    else if (qrt4 == 4)
    {
        for (int i = 127 ; i < 256 ; i++)
        {
            for (int j = 127 ; j < 256 ; j++)
            {
                image[i][j] = fourthQuarter[i-127][j-127];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }

}
void blur(){

}
