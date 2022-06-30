//
// Created by 刘科 on 2022/6/25.
//

#include "shader.h"
#include "file/file_util.h"
namespace plan9 {
    std::tuple<bool, GLuint, std::string> shader::create_vertex_shader(const std::string &path) {
        size_t size = file_util::get_size_from_file(path);
        char *buf = new char[size + 1]();
        bool suc = file_util::get_content_from_file(path, buf, size);
        if (!suc) {
            return {false, 0, ""};
        }
        buf[size] = '\0';
        auto ret = create_vertex_shader_from_context(buf);
        delete []buf;
        return ret;
    }

    std::tuple<bool, GLuint, std::string> shader::create_vertex_shader_from_context(const char *context) {
        GLuint vertex_shader = 0;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &context, NULL);
        glCompileShader(vertex_shader);
        int success;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
            return {false, 0, std::string(infoLog)};
        }
        return {true, vertex_shader, ""};
    }

    std::tuple<bool, GLuint, std::string> shader::create_fragment_shader(const std::string &path) {
        size_t size = file_util::get_size_from_file(path);
        char *buf = new char[size + 1]();
        bool suc = file_util::get_content_from_file(path, buf, size);
        if (!suc) {
            return {false, 0, ""};
        }
        buf[size] = '\0';
        auto ret = create_fragment_shader_from_context(buf);
        delete []buf;
        return ret;
    }

    std::tuple<bool, GLuint, std::string> shader::create_fragment_shader_from_context(const char *context) {
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &context, NULL);
        glCompileShader(fragment_shader);
        int success;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
            return {false, 0, std::string(infoLog)};
        }
        return {true, fragment_shader, ""};
    }

    std::tuple<bool, GLuint, std::string>
    shader::compile_shader(const std::string &vertex_path, const std::string &fragment_path) {
        auto vertex_shader = create_vertex_shader(vertex_path);
        auto fragment_shader = create_fragment_shader(fragment_path);
        if (std::get<0>(vertex_shader) && std::get<0>(fragment_shader)) {
            return compile_shader(std::get<1>(vertex_shader), std::get<1>(fragment_shader));
        }
        return {false, 0, "shader error"};
    }

    std::tuple<bool, GLuint, std::string> shader::compile_shader(GLuint vertex_shader, GLuint fragment_shader) {
        GLuint shader_program = glCreateProgram();
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);
        // check for linking errors
        int success;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
            return {false, 0, std::string(infoLog)};
        }
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return {true, shader_program, ""};
    }
}