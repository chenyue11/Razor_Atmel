/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  LedOff(BLUE);
  LedOff(YELLOW);
  LedOff(RED);
  LedOff(PURPLE);
  LedOff(WHITE);
  LedOff(ORANGE);
  LedOff(CYAN);
  LedOff(GREEN);
 /* LedOn(BLUE);
  LedToggle(PURPLE);
  LedPWM(RED,Led_PWM10);
  LedBlink(RED, LED_2HZ);*/
  
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
   // UserApp1_StateMachine =BCD_code_display;
    //UserApp1_StateMachine =button_pressed;
   // UserApp1_StateMachine =passord_button;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */
/*void passord_button(void)
{
  static u8 u8_passord[4]={0,2,3,1};
  static u8 u8_input_button[4]= 0;
  static u8 u8_counter_button_press= 0;
  static BOOL B_Pass_No[3]= FALSE;
  u8 u8_counter;
  if(WasButtonPressed(BUTTON0))
  {
    u8_input_button[u8_counter_button_press]=0;
    ButtonAcknowledge(BUTTON0);
    u8_counter_button_press++;
  }
  if(WasButtonPressed(BUTTON1))
  {
    u8_input_button[u8_counter_button_press]=1;
    ButtonAcknowledge(BUTTON1);
    u8_counter_button_press++;
  }
  if(WasButtonPressed(BUTTON2))
  {
    u8_input_button[u8_counter_button_press]=2;
    ButtonAcknowledge(BUTTON2);
    u8_counter_button_press++;
  }
    if(WasButtonPressed(BUTTON3))
  {
    u8_input_button[u8_counter_button_press]=3;
    ButtonAcknowledge(BUTTON3);
    u8_counter_button_press++;
  }
  for(u8_counter=0;u8_counter<4;u8_counter++)
  {
    if(u8_input_button[u8_counter]==u8_passord[u8_counter])
      LedOn(BLUE);
    else
      LedOn(RED);
  }
  
    
}*/


/*void button_pressed(void)
{
  static bool B_ispressed[3]=FALSE;
  if(IsButtonPressed(BUTTON0)==TRUE)
  {
    if(B_ispressed[0]=FALSE)
    { 
      LedOn(RED);
      B_ispressed[0]=TRUE;
    }
    else
    {
      LedOff(RED);
      B_ispressed[0]=FALSE;
    }
  }
  if(WasButtonPressed(BUTTON1)==TRUE)
  {
    if(B_ispressed[1]=FALSE)
    { 
      LedOn(BLUE);
      B_ispressed[1]=TRUE;
    }
    else
    {
      LedOff(BLUE);
      B_ispressed[1]=FALSE;
    }
    ButtonAcknowledge(BUTTON1);
  }
}*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
// 
/*void BCD_code_display(void)
{
  static u16 u16_counter = 0;
  static u8 a_u8_binary[8]= 0;
  u8 u8_temp_counter;
  u16 u16_counter1 = 0;
  u16 u16_counter2 = 0;
  if(G_u32SystemTime1ms%1000==0)
  {
    u16_counter++;
    if(u16_counter==99)
      u16_counter=0;
  }
  u16_counter1=u16_counter%10;
  for(u8_temp_counter = 7;u8_temp_counter>=4&&u8_temp_counter <=7;u8_temp_counter--)
  {
    a_u8_binary[u8_temp_counter]=u16_counter1%2;
            u16_counter1=u16_counter1/2;
  }
  u16_counter2=u16_counter/10;
  for(u8_temp_counter = 3;u8_temp_counter>=0&&u8_temp_counter <=3;u8_temp_counter--)
  {
    a_u8_binary[u8_temp_counter]=u16_counter2%2;
            u16_counter2=u16_counter2/2;
  }
  for(u8_temp_counter = 0;u8_temp_counter <=7;u8_temp_counter++)
  {
    if(a_u8_binary[u8_temp_counter]==1)
      LedOn(u8_temp_counter);
  else
      LedOff(u8_temp_counter);
  }
}
/*void double_led(void)
{
  u8 u8_counter=0;
  if(G_u32SystemTime1ms%500==0)
    for(u8_counter=0;u8_counter<=4;u8_counter++)
    {
      LedOn(u8_counter*2);
    }
  if(G_u32SystemTime1ms%2000==0)
    for(u8_counter=0;u8_counter<=4;u8_counter++)
    {
      LedOff(u8_counter*2);
    }
  if(G_u32SystemTime1ms%10000==0)
   UserApp1_StateMachine = all_led;
}*/


//all led light.
/*void all_led(void)
{u8 u8_counter=0;
  if(G_u32SystemTime1ms%1000==0)
  {
    for(u8_counter=0;u8_counter<=7;u8_counter++)
    {
      LedOn(u8_counter);
    }
  }
  if(G_u32SystemTime1ms%2000==0)
  {
    for(u8_counter=0;u8_counter<=7;u8_counter++)
    {
      LedOff(u8_counter);
    }
  }
  if(G_u32SystemTime1ms%10000==0)
   UserApp1_StateMachine = double_led;
}*/
/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static u8 GetButtonValue(void)
{ 
  u8 u8Buttonword = 0;
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    u8Buttonword = 1; 
  }

  if(WasButtonPressed(BUTTON1))
  {
    ButtonAcknowledge(BUTTON1);
    u8Buttonword = 2; 
  }
  
  if(WasButtonPressed(BUTTON2))
  {
    ButtonAcknowledge(BUTTON2);
    u8Buttonword = 3; 
  }
  
  return u8Buttonword;
}


static void UserApp1SM_Idle(void)
{
  static u8 u8RankNumber1 = 0;
  static u8 u8RankNumber2 = 0; 
  static u8 au8Password[10];
  static u8 au8RealPassword[10];
  static u8 u8TempButtonValue1 = 9;
  static u8 u8TempButtonValue2 = 9;
  static u8 u8Index;
  static bool bCheckFlag = FALSE;
  static bool bCheckword = TRUE;
  static bool bInputRealCodeReady = FALSE;
  static bool bRealCodeComplete = FALSE;
  static bool blightswitch = FALSE;
  
  //prepare to set code
  if(IsButtonHeld(BUTTON3,2000))
  {
    bInputRealCodeReady = TRUE;
    ButtonAcknowledge(BUTTON3);
    blightswitch = TRUE;
    bRealCodeComplete = FALSE;
    for(u8Index = 0;u8Index<u8RankNumber1;u8Index++)
    {
      au8RealPassword[u8Index] = 0;
    }
    u8RankNumber1 = 0;
  }
  
  //light switch
  if(blightswitch)
  {
    LedBlink(RED,LED_2HZ);
    LedBlink(GREEN,LED_2HZ);
     blightswitch = FALSE;
  }

  //start set code
  if(bInputRealCodeReady)
  { 

    u8TempButtonValue1 = GetButtonValue();
    if((u8TempButtonValue1 == 1)||(u8TempButtonValue1 == 2)||(u8TempButtonValue1 == 3))
    {
      au8RealPassword[u8RankNumber1] = u8TempButtonValue1;
      u8RankNumber1++;
    }
  }
  
  //complete set code
  if(bInputRealCodeReady)
  {  
    if(WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON3);
      LedOff(RED);
      LedOff(GREEN);
      bRealCodeComplete = TRUE;
      bInputRealCodeReady = FALSE;
      blightswitch = FALSE;
    } 
  } 
  
  
  //check code
  if(bRealCodeComplete)
  {
    u8TempButtonValue2 = GetButtonValue();
    if((u8TempButtonValue2 == 1)||(u8TempButtonValue2 == 2)||(u8TempButtonValue2 == 3))
    {
      au8Password[u8RankNumber2] = u8TempButtonValue2;
      u8RankNumber2++;
    }
    if(WasButtonPressed(BUTTON3))  
    {
      ButtonAcknowledge(BUTTON3);
      bCheckFlag = TRUE;
    }
    if(bCheckFlag)
    {
      for(u8Index = 0;u8Index<u8RankNumber1;u8Index++)
      {
        if(au8Password[u8Index]!=au8RealPassword[u8Index])
        {
          bCheckword = FALSE;
          break;
        }
      }
      if(bCheckword)
      {
        LedBlink(GREEN,LED_2HZ);
        LedOff(RED);
      }
      else
      {
        LedBlink(RED,LED_2HZ);
        LedOff(GREEN);
      }
      
      bCheckFlag = FALSE;
      bCheckword=TRUE;
      for(u8Index = 0;u8Index<u8RankNumber2;u8Index++)
      {
        au8Password[u8Index] = 0;
      }
      u8RankNumber2 = 0;
            
    }
  }
    
}

  /*static bool B_ispressed[3]=FALSE;
  if(IsButtonPressed(BUTTON0)==TRUE)
  {
    if(B_ispressed[0]=FALSE)
    { 
      LedOn(RED);
      B_ispressed[0]=TRUE;
    }
    else
    {
      LedOff(RED);
      B_ispressed[0]=FALSE;
    }
  }
  if(WasButtonPressed(BUTTON1)==TRUE)
  {
    if(B_ispressed[1]=FALSE)
    { 
      LedOn(BLUE);
      B_ispressed[1]=TRUE;
    }
    else
    {
      LedOff(BLUE);
      B_ispressed[1]=FALSE;
    }
    ButtonAcknowledge(BUTTON1);
  }
}*/
  /*static u8 u8_pwm_red=0;
  if(G_u32SystemTime1ms%1000==0)
  {
    LedToggle(PURPLE);
    u8_pwm_red++;
    if(u8_pwm_red>=20)
      u8_pwm_red=0;
    LedPWM(RED,u8_pwm_red);
  }*/

     /* static u8 u8key=0;
  static u32 u32Counter1 = 0;
  static u32 u32Counter2 = 1;
  static u32 u32Counter3 = 1000;
  static u32 u32Counter4 = 100;
  if(u32Counter2==1001)
  {
    u8key=1;
    u32Counter4 = 100;
  }
  else if(u32Counter2 == 1|| u32Counter4 == 1000)
  {
    u8key=0;
    u32Counter2 = 1;
  }
  switch(u8key)
  {
  case 0:u32Counter1++;
      if(u32Counter1==u32Counter2)
      { 
        LedOn(RED);
      }
       else if(u32Counter1 == 1000)
      {
           LedOff(RED);
           u32Counter1 = 0;
           u32Counter2+=100;
           u32Counter4-=1;
  }break;
  case 1:
    u32Counter3--;
    if(u32Counter3 == 0)
    { 
      LedOff(RED);
      u32Counter3 = 1000;
    }
    else if (u32Counter3 == u32Counter4)
    {   LedOn(RED);
    u32Counter4 += 100;
    u32Counter2 -= 100;
     }break;
  }
}*/

/*  u8 u8randCounter;
  u32 u32Counter1 = 0;
  u8randCounter=rand()%8;
switch(u8randCounter)
   {   
      case 0:
             LedOn(RED);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
             
             LedOff(RED);break;
      case 1:
             LedOn(BLUE);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
            
             LedOff(BLUE);break;
      case 2:
             LedOn(GREEN);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
            
             LedOff(GREEN);break;
      case 3:
             LedOn(YELLOW);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
            
             LedOff(YELLOW);break;
      case 4:
             LedOn(PURPLE);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
           
             LedOff(PURPLE);break;
      case 5:
             LedOn(ORANGE);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
           
             LedOff(ORANGE);break;
      case 6:
             LedOn(WHITE);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
           
             LedOff(WHITE);break;
      case 7:
             LedOn(CYAN);
             for(u32Counter1=0;u32Counter1<2000*500;u32Counter1++);
           
             LedOff(CYAN);break;
   }   
}
 /* static u8 u8key=0;
  static u32 u32Counter1 = 0;
  static u32 u32Counter2 = 1024;
  if(u32Counter2==2)
  {
    u8key=1;
  }
  else if(u32Counter2==1024)
  { 
    u8key=0;
  }
  switch(u8key)
  {
  case 0:u32Counter1++;
      if(u32Counter1==u32Counter2)
      LedOn(BLUE);//HEARTBEAT_ON();
       else if(u32Counter1==2*u32Counter2)
      {
           LedOff(BLUE);
           //HEARTBEAT_OFF();
           u32Counter1 = 0;
           u32Counter2/=2;
  }break;
  case 1:u32Counter1++;
       if(u32Counter1==u32Counter2)
         LedOn(BLUE);
       //HEARTBEAT_ON();
       else if(u32Counter1==2*u32Counter2)
         {
           LedOff(BLUE);
           //HEARTBEAT_OFF();
           u32Counter1 = 0;
           u32Counter2*=2;
  }break;
 }
}
} /* end UserApp1SM_Idle() */
     
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */

