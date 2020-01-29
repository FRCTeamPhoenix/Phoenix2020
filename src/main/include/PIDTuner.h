#ifndef PIDTUNER_H
#define PIDTUNER_H

class PIDTuner {
    private:
        double P, I, D, s, r, t, i, l;
    
    public:
        PIDTuner();
        ~PIDTuner();
        void set_pos(double se);
        double get_pos();
        void init();
        void calc();
        void send();
        void recv();
        void load();
        void dump(double P, double I, double D);
};

#endif 