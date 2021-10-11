class Solution {
public:
    double angleClock(int hour, int minutes) {
        // hour hand, referred to 00
        double h = (hour % 12) + minutes / 60.0; // NOTE, 60.0
        double hangle = 360.0 / 12 * h;
        
        double mangle = 360.0 / 60 * minutes;
                
        double angle = abs(mangle - hangle);
        
        return (angle <= 180) ? angle : (360 - angle);
    }
};