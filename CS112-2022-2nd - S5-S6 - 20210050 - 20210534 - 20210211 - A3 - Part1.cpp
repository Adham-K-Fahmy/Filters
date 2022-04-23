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
unsigned char newImage[256][256];


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
            cout << "please enter your choice 90 or 180 or 270 : \n";
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
void openPicture2()
{
    cout << "Please enter the name of the second image:\n";
    char imageName[100];
    cin >> imageName;
    strcat(imageName, ".bmp");
    readGSBMP(imageName, newImage);
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
    // variable for calculating the average of the photo's values
    long long average = 0;
    // loops over each pixel and adds it's sum to the average variable
    for(int x = 0; x<SIZE; x++){
        for(int y = 0; y<SIZE; y++){
            average += image[x][y];
        }
    }
    // divides the total of the values over the number of the pixels
    average /= (SIZE*SIZE);
    // loops over every pixel and checks if it's value is bigger than the average then it sets the pixel to black if not it sets it to whit
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
    // loops over every pixel and inverts it by making it's value = 255-value
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }

}
void _merge(){
    // gets a new image from the user to merge with the first one
    openPicture2();
    // loops through every pixel in newImage and sets it to it's average with image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(image[i][j] + newImage[i][j])/2;
        }
    }
}
void flip(){
    cout << "please choose how to flip the image\n1- horizontally\n2- vertically\n";
    // checks whether the user wants to flip the image horizontally or vertically
    int choose;
    cin >> choose;
    if(choose == 1){
        int temp=0;
        // loops through every pixel on the first half and swaps it's value with the pixel on the opposite side of it on the x-axis
        for(int x = 0; x<SIZE; x++){
            for(int y = 0; y<SIZE/2; y++){
                swap(image[x][y], image[x][255-y]);
            }
        }
    }
    else{
        int temp=0;
        // loops through every pixel on the first half and swaps it's value with the pixel on the opposite side of it on the y-axis
        for(int x = 0; x<SIZE/2; x++){
            for(int y = 0; y<SIZE; y++){
                swap(image[x][y], image[255-x][y]);
            }
        }
    }
}
void _rotate(){
    unsigned char newImage[SIZE][SIZE];
    // loops through every pixel in newImage and sets it's value to image[column][255-row]
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            newImage[i][j] = image[255-j][i];
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = newImage[i][j];
        }
    }


}
void darkenLighten(){
        int choice;
        cout << "if you want to lighten the image please enter 1" << endl << "or enter 2 to darken the image :";
        // checks whether the user wants to darken the picture or lighten it
        cin >> choice;
        if (choice == 1) {
            // loops through every pixel and increases it by 50% of it's value
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i][j] = (image[i][j] + 255) / 2;
                }
            }
        } else if (choice == 2) {
            // loops through every pixel and decreases it by 50% of it's value
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    image[i][j] *= 0.5;
                }
            }
        } else {
            cout << "Please enter a valid choice";
        }
}
void detectEdges(){
    // loops through every pixel then checks if the difference between it and the pixel next to it or the pixel below it is higher than 35
    // if it is it sets that pixel to black it not it sets it to white
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
    unsigned char firstQuarter[128][128];
    unsigned char secondQuarter[128][128];
    unsigned char thirdQuarter[128][128];
    unsigned char fourthQuarter[128][128];
    int userChoice;
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    cin >> userChoice;

    if (userChoice == 1)
    {
        // gets the first quarter
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                firstQuarter[i][j] = image[i][j];
            }
        }
        // enlarges the first quarter
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
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
        // gets the second quarter
        for (int i = 0; i < 128; i++)
        {
            for (int j = 128; j < 256; j++)
            {
                secondQuarter[i][j-128] = image[i][j];
            }
        }
        // enlarges the second quarter
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[2*i][2*j] = secondQuarter[i][j];
            }
        }
        // fills the empty pixels
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        // fills the empty pixels
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
        // enlarges the third quarter
        for (int i = 128; i < 256; i++)
        {
            for (int j = 0; j < 127; j++)
            {
                thirdQuarter[i-128][j] = image[i][j];
            }
        }
        // enlarges the third quarter
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[2*i][2*j] = thirdQuarter[i][j];
            }
        }
        // fills the empty pixels
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        // fills the empty pixels
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
        // enlarges the fourth quarter
        for (int i = 128; i < 256; i++)
        {
            for (int j = 128; j < 256; j++)
            {
                fourthQuarter[i-128][j-128] = image[i][j];
            }
        }
        // enlarges the fourth quarter
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[2*i][2*j] = fourthQuarter[i][j];
            }
        }
        // fills the empty pixels
        for (int i = 0 ; i < 256 ; i++)
        {
            for (int j = 1 ; j < 256 ; j+=2)
            {
                image[i][j] = image[i][j-1];
            }
        }
        // fills the empty pixels
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
    int factor;
    cout << "Please enter the factor to shrink the image dimensions by it :\n";
    // gets the new size of the photo from the user
    cin >> factor;
    if (factor <= 1)
        cout << "Please enter a valid input\n";
    else{
        // shrinks the photo
        for (int i = 0; i < SIZE; i++ ){
            for (int j = 0; j< SIZE; j++) {
                image[i/factor][j/factor]=image[i][j];
                image[i][j] = 255;
            }
        }
    }

}
void mirror(){
    int startRowPixel;
    int endRowPixel;
    int startColumnPixel;
    int endColumnPixel;
    int a;
    cout << "1- right \n2- left \n3- down \n4- up" << endl;
    // checks which half the user wants to mirror
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
    // loops through every pixel in the half that will be mirrored and puts it in the other half
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
    unsigned char firstQuarter[128][128];
    unsigned char secondQuarter[128][128];
    unsigned char thirdQuarter[128][128];
    unsigned char fourthQuarter[128][128];
    int qrt1 , qrt2 , qrt3 , qrt4;
    cout << "New order of quarters ?";
    cin >> qrt1 >> qrt2 >> qrt3 >> qrt4;

    // gets the four quarters
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            firstQuarter[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < 128; i++)
    {
        for (int j = 128; j < 256; j++)
        {
            secondQuarter[i][j-128] = image[i][j];
        }
    }
    for (int i = 128; i < 256; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            thirdQuarter[i-128][j] = image[i][j];
        }
    }
    for (int i = 128; i < 256; i++)
    {
        for (int j = 128; j < 256; j++)
        {
            fourthQuarter[i-128][j-128] = image[i][j];
        }
    }

    // checks the first quarter that the user chose and puts it in the image's first quarter
    if (qrt1 == 1)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = firstQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 2)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = secondQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 3)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = thirdQuarter[i][j];
            }
        }
    }

    else if (qrt1 == 4)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = fourthQuarter[i][j];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }

    // checks the second quarter that the user chose and puts it in the image's second quarter
    if (qrt2 == 1)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = firstQuarter[i][j-128];
            }
        }
    }

    else if (qrt2 == 2)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = secondQuarter[i][j-128];
            }
        }
    }

    else if (qrt2 == 3)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = thirdQuarter[i][j-128];
            }
        }
    }

    else if (qrt2 == 4)
    {
        for (int i = 0 ; i < 128 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = fourthQuarter[i][j-128];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }
    // checks the third quarter that the user chose and puts it in the image's third quarter
    if (qrt3 == 1)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = firstQuarter[i-128][j];
            }
        }
    }

    else if (qrt3 == 2)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = secondQuarter[i-128][j];
            }
        }
    }

    else if (qrt3 == 3)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = thirdQuarter[i-128][j];
            }
        }
    }

    else if (qrt3 == 4)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 0 ; j < 128 ; j++)
            {
                image[i][j] = fourthQuarter[i-128][j];
            }
        }
    }
    else
    {
        cout << "not valid input";
    }

    // checks the fourth quarter that the user chose and puts it in the image's fourth quarter
    if (qrt4 == 1)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = firstQuarter[i-128][j-128];
            }
        }
    }

    else if (qrt4 == 2)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = secondQuarter[i-128][j-128];
            }
        }
    }

    else if (qrt4 == 3)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = thirdQuarter[i-128][j-128];
            }
        }
    }

    else if (qrt4 == 4)
    {
        for (int i = 128 ; i < 256 ; i++)
        {
            for (int j = 128 ; j < 256 ; j++)
            {
                image[i][j] = fourthQuarter[i-128][j-128];
            }
        }
    }
    else
    {
        cout << "Not valid input";
    }

}
void blur(){
    int pixels_average;
    // blurs the picture by setting every pixel to the average of that pixel and the pixels near to it
    for (int i = 0; i < SIZE; i++ ){
        for (int j = 0; j< SIZE; j++) {
            pixels_average=(image[i][j]+ image[i][j-1]+image[i][j-2]+image[i][j+1]+image[i][j+2]+image[i-1][j]+image[i-1][j-1]+image[i-1][j-2]+image[i-1][j+1]+image[i-1][j+2]+image[i-2][j]+image[i-2][j-1]+image[i-2][j-2]+image[i-2][j+1]+image[i-2][j+2]+image[i+1][j]+image[i+1][j-1]+image[i+1][j-2]+image[i+1][j+1]+image[i+1][j+2]+image[i+2][j]+image[i+2][j-1]+image[i+2][j-2]+image[i+2][j+1]+image[i+2][j+2])/25;
            image[i][j]= pixels_average ;
        }
    }
}
