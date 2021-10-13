//::::::::::::::::::::::::HURKAN UGUR 20160702051:::::::::::::::::::::::::::::
//:::::::::::::::::::::COMPUTER GRAPHICS ASSIGNMENT:::::::::::::::::::::::::::
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
unsigned int HURKAN_TIMER_SPEED = 20;
float HURKAN_SPEED_X = 0;
float HURKAN_SPEED_Y = 0;
float HURKAN_BALL_SPEED = 0;
float HURKAN_ROTATION_DIRECTION = -1;
float HURKAN_ROTATION_SPEED = 0;
float HURKAN_SPEED_INCREMENT_X = 0;
float HURKAN_SPEED_INCREMENT_Y = 0;
int GAME_STATUS_FAILED = 0;
int GAME_STATUS_SUCCESS = 0;
void init()
{
    //BACKGROUND COLOR
    glClearColor(0, 1, 1, 1);
    glClear(GL_MATRIX_MODE);
    //COORDINATE SYSTEM IS SET TO X:[0,10] AND Y:[0:10]
    gluOrtho2D (0,10,0,10);
}
void hurkanTimer(void)
{
    if(GAME_STATUS_FAILED == 0 && GAME_STATUS_SUCCESS == 0)
    {
        glutPostRedisplay();
        glutTimerFunc(HURKAN_TIMER_SPEED, hurkanTimer, 0);
    }
}
void hurkanEnemyBall(void)
{
    //CIRCLE DRAWING ALGORITHM: https://www.youtube.com/watch?v=alL6FAH8pL4
    glPushMatrix(); //MAKE SURE THAT THE CHANGES AFFECT ONLY THIS AREA
    GLfloat x = 10.5f; GLfloat y = 1.3f; GLfloat r = 0.8f;
    glTranslatef(-1*HURKAN_BALL_SPEED,0,0); //BALL ACCELERATION MOVEMENT

    glTranslatef(x, y, 0); //ROTATION POINT
    glRotatef(HURKAN_ROTATION_SPEED,0,0,1); //ANGLE,0,0,1
    glTranslatef(-1*x, -1*y, 0); //NEGATIVE OF ROTATION POINT

    glBegin(GL_TRIANGLE_FAN);
    int triangleNumber = 60;
    glVertex2f(x,y);
    int i;
    for(i = 0; i <= triangleNumber; i++)
    {
        //STYLISH COLOURS
        if(GAME_STATUS_FAILED == 0)
        {
            if(i%2 == 0)glColor3ub(0,0,255);
            else glColor3ub(0,0,150);
        }
        else if(GAME_STATUS_FAILED == 1)
        {
            if(i%2 == 0)glColor3ub(255,255,255);
            else glColor3ub(255,0,0);
        }
        if(GAME_STATUS_SUCCESS == 1)
        {
            if(i%2 == 0)glColor3ub(255,255,255);
            else glColor3ub(0,0,255);
        }
        glVertex2f(
                   x + (r * cos(i*M_PI*2/triangleNumber)),
                   y + (r * sin(i*M_PI*2/triangleNumber))
                   );
    }
    glEnd();
    glPopMatrix(); //CHANGES ARE DONE

    glFlush();
}
void hurkanHouseDesign(void)
{
    //HOUSE DOTS
    glBegin(GL_POINTS);
    glColor3ub(0,0,0);
    float i,j;
    for(i = 0.2; i <= 9.8; i = i + 0.2)
        for(j = 5.8; j <= 9.8; j = j + 0.2)
            glVertex2f(i, j);
    glEnd();

    //HOUSE ROOF
    glBegin(GL_TRIANGLES);
    glColor3ub(255,0,0);
    glColor3ub(100,200,255);
    glVertex2f(5.0,8.0);
    glColor3ub(200,100,150);
    glVertex2f(9.0,8.0);
    glColor3ub(100,100,255);
    glVertex2f(7.0,9.0);
    glEnd();

    //HOUSE ROOF LINES
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.0,8.0);
    glVertex2f(7.0,9.0);
    glVertex2f(7.0,9.0);
    glVertex2f(9.0,8.0);
    glEnd();

    //HOUSE BODY
    glBegin(GL_QUADS);
    glColor3ub(200,200,150);
    glVertex2f(5.0,6.0);
    glColor3ub(100,200,255);
    glVertex2f(9.0,6.0);
    glColor3ub(200,200,150);
    glVertex2f(9.0,8.0);
    glColor3ub(100,200,255);
    glVertex2f(5.0,8.0);
    glEnd();

    //HOUSE BODY LINES
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    for(i = 5.0; i <= 9.0; i++)
    {
        glVertex2f(i,6.0);
        glVertex2f(i,8.0);
    }
    for(i = 6.0; i<= 8.0; i+= 0.666)
    {
        glVertex2f(5.0,i);
        glVertex2f(9.0,i);
    }
    glEnd();

    glFlush();
}

void hurkanAIRobot(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //DELETES OLD DRAWINGS

    hurkanHouseDesign(); //DRAW HOUSE

    glPushMatrix();//WILL BE APPLIED TO ALL BODY PART (MOVEMENTS)
    glTranslatef(HURKAN_SPEED_X, HURKAN_SPEED_Y,0); //CHANGE BODY PARTS X,Y VALUES AT THE SAME TIME

    //BODY
    glBegin(GL_QUADS);
    glColor3ub(100,200,250);
    glVertex2f(1,4);
    glColor3ub(200,250,200);
    glVertex2f(2,4);
    glColor3ub(250,200,205);
    glVertex2f(2,2);
    glColor3ub(200,250,250);
    glVertex2f(1,2);
    glEnd();


    //ARMS
    glPushMatrix(); //MAKE SURE THAT THE CHANGES AFFECT ONLY THIS AREA
    if(HURKAN_SPEED_INCREMENT_X >= 0){
        //PLAYER GOES TO RIGHT (ARM IS DRAWN ON THE RIGHT SIDE)
        glTranslatef(2, 3.25, 0); //ROTATION POINT
        glRotatef(-50,0,0,1); //ANGLE,0,0,1
        glTranslatef(-2, -3.25, 0); //NEGATIVE OF ROTATION POINT
    }
    else
    {
        //PLAYER GOES TO LEFT (ARM IS DRAWN ON THE LEFT SIDE)
        glTranslatef(1.4, 3.45, 0); //ROTATION POINT
        glRotatef(-140,0,0,1); //ANGLE,0,0,1
        glTranslatef(-1.4, -3.45, 0); //NEGATIVE OF ROTATION POINT
    }

    glBegin(GL_QUADS); // DRAW A RECTANGLE
    glColor3ub(100,200,250);
    glVertex2f(1.5,3.5);
    glColor3ub(200,250,200);
    glVertex2f(2.5,3.5);
    glColor3ub(250,200,205);
    glVertex2f(2.5,3);
    glColor3ub(200,250,250);
    glVertex2f(1.5,3);
    glEnd();
    glPopMatrix(); //CHANGES ARE DONE


    //HEAD
    //CIRCLE DRAWING ALGORITHM: https://www.youtube.com/watch?v=alL6FAH8pL4
    glBegin(GL_TRIANGLE_FAN);
    GLfloat head_x = 1.5f; GLfloat head_y = 4.5f; GLfloat head_r = 0.5f;
    int triangleNumber = 60;
    glVertex2f(head_x,head_y);
    int i;
    //PLAYER GOES TO THE RIGHT (PLAYER LOOKS AT THE RIGHT SIDE)
    if(HURKAN_SPEED_INCREMENT_X >= 0){
        for(i = 0; i <= triangleNumber-5; i++)
        {
            //STYLISH COLOURS
            glColor3ub(190,190,255);
            glVertex2f(
                       head_x + (head_r * cos(i*M_PI*2/triangleNumber)),
                       head_y + (head_r * sin(i*M_PI*2/triangleNumber))
                       );
        }
    }
    //PLAYER GOES TO THE LEFT (PLAYER LOOKS AT THE LEFT SIDE)
    else{
        for(i = triangleNumber-5; i >= 0; i--)
        {
            //STYLISH COLOURS
            glColor3ub(190,190,255);
            glVertex2f(
                       head_x + (head_r*-1 * cos(i*M_PI*2/triangleNumber)),
                       head_y + (head_r * sin(i*M_PI*2/triangleNumber))
                       );
        }
    }
    glEnd();


    //FOOT
    //CIRCLE DRAWING ALGORITHM: https://www.youtube.com/watch?v=alL6FAH8pL4
    glPushMatrix(); //MAKE SURE THAT THE CHANGES AFFECT ONLY THIS AREA
    GLfloat foot_x = 1.5f; GLfloat foot_y = 1.5f; GLfloat foot_r = 1.0f;
    glTranslatef(foot_x, foot_y, 0); //ROTATION POINT
    glRotatef(HURKAN_ROTATION_SPEED*HURKAN_ROTATION_DIRECTION,0,0,1); //ANGLE,0,0,1
    glTranslatef(-1*foot_x, -1*foot_y, 0); //NEGATIVE OF ROTATION POINT

    glBegin(GL_TRIANGLE_FAN);
    triangleNumber = 60;
    glVertex2f(foot_x,foot_y);
    for(i = 0; i <= triangleNumber; i++)
    {
        //STYLISH COLOURS
        if(i%2 == 0)glColor3ub(224,224,208);
        else glColor3ub(224,224,208);

        glVertex2f(
                   foot_x + (foot_r * cos(i*M_PI*2/triangleNumber)),
                   foot_y + (foot_r * sin(i*M_PI*2/triangleNumber))
                   );
    }
    glEnd();
    glPopMatrix(); //CHANGES ARE DONE


    //FOOT LINES
    glPushMatrix(); //MAKE SURE THAT THE CHANGES AFFECT ONLY THIS AREA
    glTranslatef(1.5, 1.5, 0); //ROTATION POINT
    glRotatef(HURKAN_ROTATION_SPEED*HURKAN_ROTATION_DIRECTION,0,0,1); //ANGLE,0,0,1
    glTranslatef(-1.5, -1.5, 0); //NEGATIVE OF ROTATION POINT

    glBegin(GL_LINES);
    glColor3b(0,0,0);
    glVertex2f(0.5,1.5);
    glVertex2f(2.5,1.5);
    glVertex2f(1.5,0.5);
    glVertex2f(1.5,2.5);
    glEnd();
    glPopMatrix(); //CHANGES ARE DONE

    glPopMatrix(); //END OF THE TRANSMISSION OF ALL BODY PARTS


    //INCREASE X UNTIL IT REACHES MIN/MAX WIDTH
    HURKAN_SPEED_X += HURKAN_SPEED_INCREMENT_X;
    HURKAN_SPEED_Y += HURKAN_SPEED_INCREMENT_Y;
    HURKAN_ROTATION_SPEED += 3;
    HURKAN_BALL_SPEED += 0.05;

    //IF EITHER BALL OR ROBOT REACHES THE BOUNDRIES, STABILIZE THEIR POSITION
    if(HURKAN_BALL_SPEED > 11.5)
        HURKAN_BALL_SPEED = 0;
    if(HURKAN_SPEED_X < -0.3)
        HURKAN_SPEED_X = -0.3;
    if(HURKAN_SPEED_X > 7.5){
        GAME_STATUS_SUCCESS = 1;
        for(i=0; i<10;i++)
            printf("[GAME OVER]: YOU WON\n");
    }
    //GRAVITY SETTINGS: INCREASE Y UNTIL IT REACHES MAX HEIGHT
    if(HURKAN_SPEED_Y > 3)
        HURKAN_SPEED_INCREMENT_Y *= -1;
    if(HURKAN_SPEED_INCREMENT_Y < 0)
    {
        if(HURKAN_SPEED_Y <= 0)
        {
            HURKAN_SPEED_Y = 0;
            HURKAN_SPEED_INCREMENT_Y = 0;
        }
    }

    //COLLISION CONTROL
    if(HURKAN_SPEED_Y == 0.0){
        if(abs((HURKAN_SPEED_X + 1.5) - (HURKAN_BALL_SPEED*-1 + 9.7)) == 0.0) //WHEN PLAYER GOES TO THE RIGHT AND COLLISION OCCURS
        {
            GAME_STATUS_FAILED = 1;
            for(i=0; i<10;i++)
                printf("[GAME OVER]: YOU LOST\n");
        }
        else if(abs((HURKAN_SPEED_X + 1.5) - (HURKAN_BALL_SPEED*-1 + 11.3)) == 0.0) //WHEN PLAYER GOES TO THE LEFT AND COLLISION OCCURS
        {
            GAME_STATUS_FAILED = 1;
            for(i=0; i<10;i++)
                printf("[GAME OVER]: YOU LOST\n");
        }
    }

    hurkanEnemyBall(); //DRAW ENEMY BALL
    glFlush();
}
void HURKAN_KEYBOARD_EVENT_HANDLER(char key)
{
    switch(key)
    {
        case GLUT_KEY_RIGHT: //RIGHT ARROW
        case 'D':
        {
            HURKAN_SPEED_INCREMENT_X = 0.05;
            HURKAN_ROTATION_DIRECTION = -1; //CLOCKWISE ROTATION
            break;
        }
        case GLUT_KEY_LEFT: //LEFT ARROW
        case 'A':
        {
            HURKAN_SPEED_INCREMENT_X = -0.05;
            HURKAN_ROTATION_DIRECTION = 1; //COUNTER CLOCKWISE ROTATION
            break;
        }
        case GLUT_KEY_UP: //UP ARROW
        case 32: //SPACE
        case 'W':
        {
            if(HURKAN_SPEED_INCREMENT_Y == 0)
                HURKAN_SPEED_INCREMENT_Y = 0.1;
            break;
        }
    }
}
void main (int argc, char** argv)
{
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition (400, 150); // Set top-left display-window position.
    glutInitWindowSize (700, 500); // Set display-window width and height.
    glutCreateWindow ("Hurkan Ugur - Virtual World"); // Create display window.
    printf("[Movement Tips]: Turn on your CapsLock, then: {W, A, S, D, Space}\n[Movement Tips]: {Left Arrow, Right Arrow, Up Arrow}\n");
    printf("\n[Game Task]: Try to reach at the right most side of the screen !\n\n");
    init();

    //ALPHABETIC & NUMERIC KEY READER
    glutKeyboardFunc(HURKAN_KEYBOARD_EVENT_HANDLER);
    //NON ALPHABETIC & NUMERIC KEY READER
    glutSpecialFunc(HURKAN_KEYBOARD_EVENT_HANDLER);
    //DRAW THE PICTURES
    glutDisplayFunc (hurkanAIRobot);
    //ACTIVATE HUKO TIMER
    glutTimerFunc(0,hurkanTimer, 0);
    //DISPLAY EVERYTHING AND WAIT
    glutMainLoop();
}
