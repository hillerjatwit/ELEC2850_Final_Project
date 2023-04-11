#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"
#include "JTAG_UART.h"




void VGAbuild(int, int, int, int, short);
void clearScreen();
int convert(int);
void VGA_text(int, int, char*);



volatile int timeout;
volatile int pixel_buffer_start = FPGA_ONCHIP_BASE;

int resolution_x = 320;
int resolution_y = 240;

int main() {

    NIOS2_WRITE_IENABLE(0x1);
    NIOS2_WRITE_STATUS(1);

    char textLEFT[15] = "PLAYER 1 WINS\0";
    char textRIGHT[15] = "PLAYER 2 WINS\0";

    volatile int* interval_timer_ptr = (int*)TIMER_BASE;
    volatile int* sevSEG_ptr2 = (int*)HEX3_0_BASE;
    volatile int* sevSEG_ptr1 = (int*)HEX5_4_BASE;
    volatile int* JTAG_UART_ptr = (int*)JTAG_UART_BASE;


    int counter = 0x960000;		//approx 200ms
    *(interval_timer_ptr + 2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 3) = (counter >> 16) & 0xFFFF;
    *(interval_timer_ptr + 1) = 0x7;

    //starting coordinates for the ball
    short ball_cocor = 0x1CE0;
    int ballx1 = 157;
    int ballx2 = 163;
    int bally1 = 117;
    int bally2 = 123;

    //starting coordinatres for right paddle
    short right_color = 0x1CE0;
    int right_x1 = 300;
    int right_x2 = 310;
    int right_y1 = 95;
    int right_y2 = right_y1 + 50 - 1;

    //starting coordinates for left paddle
    short left_color = 0x1CE0;
    int left_x1 = 10;
    int left_y1 = 95;
    int left_x2 = left_x1 + 10 - 1;
    int left_y2 = left_y1 + 50 - 1;


    int hex_val_1 = 0x0000003F;

    *(sevSEG_ptr1) = hex_val_1;

    int hex_val_2 = 0x0000003F;

    *(sevSEG_ptr2) = hex_val_2;

    int reset = 0;

    int score1 = 0;

    int score2 = 0;


    int ball_midpoint, left_midpoint, right_midpoint;

    int left_score = 0;
    int right_score = 0;
    int SevenAeg_valR;

    int check = 0;

    ball_midpoint = (bally1 + bally2) / 2;  //finds the middle of the ball in the y-direction

    left_midpoint = (left_y1 + left_y2) / 2;

    right_midpoint = (right_y1 + right_y2) / 2;




    //y inc change per frame
    int ball_y_inc = 0;
    //Speed of the ball on the x axis
    int ball_x_speed = 1;


    char move = 'm';


    //create bar on top and bottom then set paddles and ball
    VGAbuild(0, 210, 320, 220, 0x808080);
    VGAbuild(0, 20, 320, 30, 0x808080);
    VGAbuild(ballx1, bally1, ballx2, bally2, 0x808080);
    VGAbuild(right_x1, right_y1, right_x2, right_y2, 0x808080);
    VGAbuild(left_x1, left_y1, left_x2, left_y2, 0x808080);


    while (1) {
        while (!timeout) {

            //if it hits the top or bottom of the screen
            if (bally2 == 209 || bally1 == 31) {
                ball_y_inc = -ball_y_inc;
            }
            //hits right paddle, switch x direction, and to the x direction speed
            if ((ballx2 == right_x1 - 1) && (bally1 >= right_y1) && (bally2 <= right_y2)) {
                ball_x_speed = -ball_x_speed;

            }
            //hits left paddle, switch x direction, and adds to the x direction speed
            else if ((ballx1 == left_x2 + 1) && (bally1 >= left_y1) && (bally2 <= left_y2)) {
                ball_x_speed = -ball_x_speed; //change direction of ball


            }

            if ((ballx1 == left_x2) && (bally1 >= left_y1) && (bally2 <= left_y2)) { //if ball hits left paddle
                if ((ball_midpoint >= left_midpoint - 4) && (ball_midpoint <= left_midpoint + 3)) {
                    ball_y_inc = 0;
                }

                else if ((ball_midpoint >= left_midpoint - 10) && (ball_midpoint <= left_midpoint - 5)) {
                    ball_y_inc = -1;

                }

                else if ((ball_midpoint >= left_midpoint + 4) && (ball_midpoint <= left_midpoint + 9)) {
                    ball_y_inc = 1;

                }

                else if ((ball_midpoint >= left_midpoint - 17) && (ball_midpoint <= left_midpoint - 11)) {
                    ball_y_inc = -2;

                }

                else if ((ball_midpoint >= left_midpoint + 10) && (ball_midpoint <= left_midpoint + 16)) {
                    ball_y_inc = 2;

                }

                else if ((ball_midpoint >= left_midpoint - 25) && (ball_midpoint <= left_midpoint - 18)) {
                    ball_y_inc = -3;

                }

                else if ((ball_midpoint >= left_midpoint + 17) && (ball_midpoint <= left_midpoint + 24)) {
                    ball_y_inc = 3;

                }



            }

            if ((ballx2 == right_x1) && (bally1 >= right_y1) && (bally2 <= right_y2)) { //if ball hits right paddle
                if ((ball_midpoint >= right_midpoint - 4) && (ball_midpoint <= right_midpoint + 3)) {
                    ball_y_inc = 0;
                }

                else if ((ball_midpoint >= right_midpoint - 10) && (ball_midpoint <= right_midpoint - 5)) {
                    ball_y_inc = -1;

                }

                else if ((ball_midpoint >= right_midpoint + 4) && (ball_midpoint <= right_midpoint + 9)) {
                    ball_y_inc = 1;

                }

                else if ((ball_midpoint >= right_midpoint - 17) && (ball_midpoint <= right_midpoint - 11)) {
                    ball_y_inc = -2;

                }

                else if ((ball_midpoint >= right_midpoint + 10) && (ball_midpoint <= right_midpoint + 16)) {
                    ball_y_inc = 2;

                }

                else if ((ball_midpoint >= right_midpoint - 25) && (ball_midpoint <= right_midpoint - 18)) {
                    ball_y_inc = -3;

                }

                else if ((ball_midpoint >= right_midpoint + 17) && (ball_midpoint <= right_midpoint + 24)) {
                    ball_y_inc = 3;

                }



            }

            ballx1 += ball_x_speed;
            ballx2 += ball_x_speed;
            bally1 += ball_y_inc;
            bally2 += ball_y_inc;

            char c = get_jtag(JTAG_UART_ptr);

            if ((left_y1 == 30) || (left_y2 == 210))

            {

                if (c == 'w') {

                }

                if (c == 's') {

                }

            }

            else if ((right_y1 == 30) || (right_y2 == 210))

            {

                if (c == 'i') {

                }

                if (c == 'k') {

                }

            }

            else

            {

                switch (c)

                {

                case 'w':

                    left_y1 += 3;

                    left_y2 += 3;

                    break;

                case 's':

                    left_y1 -= 3;

                    left_y2 -= 3;

                    break;

                case 'i':

                    right_y1 += 3;

                    right_y2 += 3;

                    break;

                case 'k':

                    right_y1 -= 3;

                    right_y2 -= 3;

                    break;
                default:
                    break;

                }


            }

        }

        if (ballx2 > right_x1)

        {

            reset = 1;

            score2++;

            hex_val_2 = convert(score2);

            *(sevSEG_ptr2) = hex_val_2;

        }
        else if (ballx1 < left_x2)

        {

            reset = 2;
            score1++;
            hex_val_1 = convert(score1);
            *(sevSEG_ptr1) = hex_val_1;

        }
        if (reset == 0) {



            clearScreen();
            VGAbuild(ballx1, bally1, ballx2, bally2, 0x808080);
            VGAbuild(right_x1, right_y1, right_x2, right_y2, 0x808080);
            VGAbuild(left_x1, left_y1, left_x2, left_y2, 0x808080);
            //create bar on top
            VGAbuild(0, 230, 320, 240, 0x808080);
            //create bar on bottom
            VGAbuild(0, 0, 320, 10, 0x808080);

        }


        else if (reset == 1 || reset == 2) {

            ballx1 = 157;
            ballx2 = 163;
            bally1 = 117;
            bally2 = 123;

            //starting coordinatres for right paddle

            right_x1 = 300;
            right_x2 = 310;
            right_y1 = 95;
            right_y2 = right_y1 + 50 - 1;

            //starting coordinates for left paddle

            left_x1 = 10;
            left_y1 = 95;
            left_x2 = left_x1 + 10 - 1;
            left_y2 = left_y1 + 50 - 1;

            if (reset == 1) {
                ball_x_speed = 1;
            }
            else {
                ball_x_speed = -1;
            }
            ball_y_inc = 0;
            reset = 0;
        }


        if (score1 == 7 || score2 == 7) {
            ballx1 = 157;
            ballx2 = 163;
            bally1 = 117;
            bally2 = 123;

            //starting coordinatres for right paddle

            right_x1 = 300;
            right_x2 = 310;
            right_y1 = 95;
            right_y2 = right_y1 + 50 - 1;

            //starting coordinates for left paddle

            left_x1 = 10;
            left_y1 = 95;
            left_x2 = left_x1 + 10 - 1;
            left_y2 = left_y1 + 50 - 1;

            ball_x_speed = 0;
            ball_y_inc = 0;

            if (score1 == 7) {
                VGA_text(157, 117, textLEFT);
            }
            else if (score2 == 7) {
                VGA_text(157, 117, textRIGHT);
            }
        }

        timeout = 0;
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

int convert(int num)                                //EDIT -- NEW FUNCTION DEFINITION

{

    int i = 0;



    if (num == 0)

        i = 0x0000003F;

    else if (num == 1)

        i = 0x00000006;

    else if (num == 2)

        i = 0x0000005B;

    else if (num == 3)

        i = 0x0000004F;

    else if (num == 4)

        i = 0x00000066;

    else if (num == 5)

        i = 0x0000006D;

    else if (num == 6)

        i = 0x0000007D;

    else if (num == 7)

        i = 0x00000007;

    else if (num == 8)

        i = 0x0000007F;

    else if (num == 9)

        i = 0x00000067;

    else if (num == 10)

        i = 0x00000077;
    else {
        i = 0;
    }



    return i;

}

void VGA_text(int x, int y, char* text_ptr) {
    int offset;
    volatile char* character_buffer = (char*)FPGA_CHAR_BASE;

    offset = (y << 7) + x;

    while (*(text_ptr)) {
        *(character_buffer + offset) = *(text_ptr);
        ++text_ptr;
        ++offset;
    }

}


