//
// Created by Patrik Aradi on 2023/10/29.
//

#ifndef OPENGL_PLAYGROUND_TEXTURE_H
#define OPENGL_PLAYGROUND_TEXTURE_H

#include <string>
#include <OpenGL/gl3.h>

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
