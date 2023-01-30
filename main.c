#include <stdio.h>


typedef enum {
    STATE_INIT = 0u,
    STATE_IDLE,
    STATE_RUNNING,
    STATE_LOW_POWER
}t_state;

typedef enum{
    NO_EVENT_RECEIVED,
    INIT_RECEIVED,
    IDLE_RECEIVED,
    START_RECEIVED,
    LOW_POWER_RECEIVED
}t_event;

static t_state current_state = STATE_INIT;

static void printf_current_state(void)
{
    switch (current_state)
    {
    case STATE_IDLE:
        /* code */
        printf("Idle ....\n");
        break;
    case STATE_RUNNING:
        printf("Running ....\n");
        break;
    case STATE_LOW_POWER:
        printf("Low power ....\n");
        break;
    default:
        break;
    }
}
//Function to get input event
static t_event get_event()
{
    char input_char;
    t_event ret = NO_EVENT_RECEIVED;
    printf_current_state();

    printf("ENTER A CHARACTER(i for idle,l for low power,r for start);\n");
    scanf("%c",&input_char);
    switch (input_char)
    {
    case 'i':
        /* code */
        ret = IDLE_RECEIVED;
        break;
    case 'r':
        ret = START_RECEIVED;
        break;
    case 'l':
        ret = LOW_POWER_RECEIVED;
        break;
    default:
        break;
    }
    return ret;
}

static void state_init(void)
{
    printf("Initializing....\n");
    current_state = STATE_IDLE;
}

static void state_idle(const t_event event)
{
    if(event == START_RECEIVED){
        current_state = STATE_RUNNING;
    }
    else if(event == LOW_POWER_RECEIVED){
        current_state = STATE_LOW_POWER;
    }
    else if((event == IDLE_RECEIVED) ||( event == NO_EVENT_RECEIVED)){

    }
    else{
        printf("invalid\n");
    }
}

static void state_running(const t_event event)
{
    if(event == LOW_POWER_RECEIVED)
    {
        current_state = STATE_LOW_POWER;
    }
    else if( event == IDLE_RECEIVED)
    {
        current_state = STATE_IDLE;
    }
    else if((event == START_RECEIVED)||(event == NO_EVENT_RECEIVED))
    {

    }
    else{
        printf("Invalid");
    }
}
static void state_low_power(const t_event event)
{
    if(event == START_RECEIVED){
        current_state = STATE_RUNNING;
    }
    else if((event == LOW_POWER_RECEIVED) || (event == NO_EVENT_RECEIVED))
    {
    }
    else{
        printf("Invalid");
    }
}

static void state_machine()
{
    const t_event event = get_event();
    switch (current_state)
    {
    case STATE_IDLE:
        /* code */
        state_idle(event);
        break;
    case STATE_RUNNING:
        state_running(event);
        break;
    case STATE_LOW_POWER:
        state_low_power(event);
        break;
    default:
        break;
    }
}
int main()
{
    state_init();
    while (1)
    {
        /* code */
        state_machine();
    }
    return 0;
}
