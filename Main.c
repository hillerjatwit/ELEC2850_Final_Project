#include <address_map_nios2.h>

void VGAbuild(int, int, int, int, short);
void clearScreen();

volatile int pixel_buffer_start = FPGA_ONCHIP_BASE;

int resolution_x = 320;
int resolution_y = 240;

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
    int left_x1 = 10;
    int left_y1 = 124;
    int left_x2 = left_x1 + 10 - 1;
    int left_y2 = left_y1 + 50 - 1;


    int ball_midpoint, left_midpoint, right_midpoint;

    int ball_inc_y;

    int check = 0;

    ball_midpoint = (bally1 + bally2) / 2;  //finds the middle of the ball in the y-direction

    left_midpoint = (left_y1 + left_y2) / 2;




    //y inc, change in the y parameter per frame
    int ball_y_inc = 0;
    int ball_x_inc = 0;

    VGAbuild(ballx1, bally1, ballx2, bally2, 0x808080);
    VGAbuild(right_x1, right_y1, right_x2, right_y2, 0x808080);
    VGAbuild(left_x1, left_y1, left_x2, left_y2, 0x808080);


    while (1) {

        //speed the ball will move over the x axis
        int ball_x_speed = 1;

        //hits right paddle, switch x direction, and to the x direction speed
        if (ballx2 == 300 && ((bally1 > right_y1) || (bally2 < right_y2))) {
            ball_x_speed = -ball_x_speed;
            ball_x_inc = -ball_x_inc;

            ball_x_speed += ball_x_inc;
         
        }
        //hits left paddle, switch x direction, and adds to the x direction speed
        else if (ballx2 == 20 && ((bally1 > left_y1) || (bally2 < left_y2))) {
            ball_x_speed = -ball_x_speed;
            ball_x_inc = -ball_x_inc;

            ball_x_speed += ball_x_inc;
            
        }
        //if it hits the top or bottom of the screen
        else if (bally1 == 229 || bally2 == 11) {
            ball_y_inc = -ball_y_inc;
        }
        if ((ballx1 == left_x2) && (bally1 >= left_y1) && (bally2 <= left_y2)) //if ball hits left paddle

        {

            if ((ball_midpoint >= left_midpoint - 1) && (ball_midpoint <= left_midpoint + 2))

            {

                ball_inc_y = 0;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint - 4) && (ball_midpoint <= left_midpoint - 2) && (check != 1))

            {

                ball_inc_y = -1;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint + 3) && (ball_midpoint <= left_midpoint + 5) && (check != 1))

            {

                ball_inc_y = 1;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint - 14) && (ball_midpoint <= left_midpoint - 5) && (check != 1))

            {

                ball_inc_y = -2;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint + 6) && (ball_midpoint <= left_midpoint + 15) && (check != 1))

            {

                ball_inc_y = 2;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint - 24) && (ball_midpoint <= left_midpoint - 15) && (check != 1))

            {

                ball_inc_y = -3;

                check = 1;

            }

            if ((ball_midpoint >= left_midpoint + 16) && (ball_midpoint <= left_midpoint + 25) && (check != 1))

            {

                ball_inc_y = 3;

                check = 1;

            }

            check = 0;

        }

        if ((ballx2 == right_x1) && (bally1 >= right_y1) && (bally2 <= right_y2)) //if ball hits right paddle

        {

            if ((ball_midpoint >= right_midpoint - 1) && (ball_midpoint <= right_midpoint + 2))

            {

                ball_inc_y = 0;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint - 4) && (ball_midpoint <= right_midpoint - 2) && (check != 1))

            {

                ball_inc_y = -1;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint + 3) && (ball_midpoint <= right_midpoint + 5) && (check != 1))

            {

                ball_inc_y = 1;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint - 14) && (ball_midpoint <= right_midpoint - 5) && (check != 1))

            {

                ball_inc_y = -2;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint + 6) && (ball_midpoint <= right_midpoint + 15) && (check != 1))

            {

                ball_inc_y = 2;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint - 24) && (ball_midpoint <= right_midpoint - 15) && (check != 1))

            {

                ball_inc_y = -3;

                check = 1;

            }

            if ((ball_midpoint >= right_midpoint + 16) && (ball_midpoint <= right_midpoint + 25) && (check != 1))

            {

                ball_inc_y = 3;

                check = 1;

            }

            check = 0;

        }

        clearScreen();
        VGAbuild(ballx1, bally1, ballx2, bally2, 0x808080);
        VGAbuild(right_x1, right_y1, right_x2, right_y2, 0x808080);
        VGAbuild(left_x1, left_y1, left_x2, left_y2, 0x808080);



    }
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