
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{

private:
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;


};
  
#endif
