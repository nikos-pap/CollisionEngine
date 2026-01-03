#pragma once
#include <iostream>
#include "opengl.h"

class OpenGLProfiler {
private:
    GLuint m_queryID;
    std::string m_name;

public:
    OpenGLProfiler(const std::string& name) : m_name(name) {
        glGenQueries(1, &m_queryID);
    }

    ~OpenGLProfiler() {
        glDeleteQueries(1, &m_queryID);
    }

    void begin() {
        glBeginQuery(GL_TIME_ELAPSED, m_queryID);
    }

    void end() {
        glEndQuery(GL_TIME_ELAPSED);
    }

    float getResultMs() {
        GLuint64 timeNs;
        glGetQueryObjectui64v(m_queryID, GL_QUERY_RESULT, &timeNs);
        return timeNs / 1000000.0f;
    }

    void printResult() {
        std::cout << m_name << ": " << getResultMs() << " ms" << std::endl;
    }
};
