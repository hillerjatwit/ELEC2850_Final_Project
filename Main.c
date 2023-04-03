#include <address_map_nios2.h>

void VGAbuild(int, int, int, int, short);
void clearScreen();

int main() {


    //create bar on top
    VGAbuild(0, 230, 320, 240, 0x808080);

    //create bar on bottom
    VGAbuild(0, 0, 320, 10, 0x808080);


    //starting coordinates for the ball
    int ballx1 = 157;
    int ballx2 = 163;
    int bally1 = 117;
    int bally2 = 123;

    //starting coordinatres for right paddle
    int right_x1 = 300;
    int right_x2 = 310;
    int right_y1 = 95;
    int right_y2 = right_y1 + 50 - 1;

    //starting coordinates for left paddle
    short player1_color = 0x1CE0;
    int player1_x1 = 10;
    int player1_y1 = 124;
    int player1_x2 = player1_x1 + 10 - 1;
    int player1_y2 = player1_y1 + 50 - 1;





    //y inc, change in the y parameter per frame
    int ball_inc = 0;






}

void VGAbuild(int x1, int y1, int x2, int y2, short pixel_color) {

    int offset, row, col;
    volatile short* pixel_buffer = (short*)0x08000000;    //VGA pixel buffer 



    for (row = y1; row <= y2; row++) {

        for (col = x1; col <= x2; col++) {

            offset = (row << 9) + col;//change the pixels color to color designated 
            *(pixel_buffer + offset) = pixel_color;

        }

    }

}

void clearScreen() {

    int clearColor = 0;
    int pixel_ptr, row, col;

    //for every pixel on the screen
    for (row = 0; row < resolution_y; row++) {
        for (col = 0; col < resolution_x; col++) {

            pixel_ptr = pixel_buffer_start + (row << 10) + (col << 1);
            *(short*)pixel_ptr = clearColor;//change to clearcolor basically get rid of everything 

        }

    }

}