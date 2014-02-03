/* control.h - header file for control.c */

void move_tank(char direc[], int time);


/* move_tank calls these */
void forward (int time);
void backward (int time);
void foright (int time);
void foleft (int time);
void baright (int time);
void baleft (int time);
void stop (int);

/* manual mode movements */
void man_f(void);
void man_b(void);
void man_fr(void);
void man_fl(void);
void man_br(void);
void man_bl(void);
void man_stop(void);

/* end of control.h */
