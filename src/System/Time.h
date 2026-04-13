#pragma once

class Time {
public:
    static void update();

    static float getDeltaTime() { return s_deltaTime; }
    static float getTime() { return s_currentTime; }
    static float getFPS() { return s_fps; }

    static void setTimeScale(float scale) { s_timeScale = scale; }
    static float getTimeScale() { return s_timeScale; }

private:
    static float s_deltaTime;
    static float s_currentTime;
    static float s_lastFrame;
    static float s_fps;
    static int s_frameCount;
    static float s_lastFPSUpdate;
    static float s_timeScale;
};