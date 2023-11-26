//
// Created by Patrik Aradi on 2023/10/29.
//

#ifndef OPENGL_PLAYGROUND_TEXTURE_H
#define OPENGL_PLAYGROUND_TEXTURE_H

#include <string>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

namespace Engine {
    class Texture {
    private:
        GLuint textureId;

    public:
        explicit Texture(const std::string &path);

        void bind() const;
        void bind(GLenum position) const;
    };

}


#endif //OPENGL_PLAYGROUND_TEXTURE_H
