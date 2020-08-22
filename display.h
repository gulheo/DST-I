#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_
void initDisplay();
unsigned char Read_status_Display(void);
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void init_Display(void);
void clear_display(void);

#endif