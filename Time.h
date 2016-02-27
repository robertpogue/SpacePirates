#pragma once

class Time {
public:
    Time();
    int frame(); // returns previous frame time in ms
private:
    int lastFrame; // timestamp in ms
};
