#include "world.hpp"

/*
#define CASE_STR( value ) case value: return #value;
/*
const char* glGetErrorString(GLenum error )
{
    switch( error )
    {
    CASE_STR(GL_NO_ERROR)
    CASE_STR(GL_INVALID_ENUM)
    CASE_STR(GL_INVALID_VALUE)
    CASE_STR(GL_INVALID_OPERATION)
    CASE_STR(GL_INVALID_FRAMEBUFFER_OPERATION)
    CASE_STR(GL_OUT_OF_MEMORY)
    default: return "Unknown";
    }
}
#undef CASE_STR
void GL_check_error(const char * at) // TODO: macro w/ line & file
{
    GLenum e = glGetError();
    if(e != GL_NO_ERROR)
    {
        using namespace std::string_literals;
        __android_log_print(ANDROID_LOG_ERROR, "Error at %s: %s", at, glGetErrorString(e));
        throw std::system_error(e, std::system_category(), "Error at "s + std::string(at) + ":\n"s + glGetErrorString(e));
    }
}

void destroy()
{
    glDeleteBuffers(1, &vbo);
    prog.reset();
    font.reset();

    vbo = 0;
    prog = 0;

}
void render_loop()
{
    __android_log_write(ANDROID_LOG_DEBUG, "RENDER_LOOP", "start render loop");
    bool window_set = false;
    glm::vec3 delta = {0.001f, 0.005f, 0.010f};
    while(true)
    {
        std::lock_guard<std::mutex> lock(render_mutex);

        if(!running)
        {
            destroy();
            break;
        }

        if(!window_set && window)
        {
            __android_log_write(ANDROID_LOG_DEBUG, "RENDER_LOOP", "init!");
            if(!init())
            {
                __android_log_write(ANDROID_LOG_ERROR, "RENDER_LOOP", "Initialization failed!");
                break;
            }
            window_set = true;
        }

        if(display == EGL_NO_DISPLAY)
        {
            //__android_log_write(ANDROID_LOG_DEBUG, "RENDER_LOOP", "no display");
            continue;
        }

        bg_color += delta;
        if(bg_color.r > 1.0f || bg_color.r < 0.0f) delta.r = -delta.r;
        if(bg_color.g > 1.0f || bg_color.g < 0.0f) delta.g = -delta.g;
        if(bg_color.b > 1.0f || bg_color.b < 0.0f) delta.b = -delta.b;

        glClearColor(bg_color.r, bg_color.g, bg_color.b, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        prog->use();
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        font->render_text("ASDF", {0.0f, 0.0f, 0.0f, 1.0f}, {width, height}, glm::vec2{width, height} / 2.0f, textogl::ORIGIN_HORIZ_CENTER | textogl::ORIGIN_VERT_CENTER);

        GL_check_error("draw");

        if(!eglSwapBuffers(display, surface))
        {
            __android_log_write(ANDROID_LOG_ERROR, "RENDER_LOOP", "couldn't swap!");
        }
    }
    __android_log_write(ANDROID_LOG_DEBUG, "RENDER_LOOP", "end render loop");
}

GLfloat verts [] =
        {
                -0.5f, -0.5f,
                -0.5f,  0.5f,
                0.5f, -0.5f,
                0.5f,  0.5f
        };

glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);

glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
GL_check_error("vao/vbo");

const char * vertshader =
        R"(attribute vec4 vert_pos;
void main()
{
    gl_Position = vert_pos;
}
)";
const char * fragshader =
        R"(precision mediump float;

void main()
{
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
)";

prog = std::make_unique<Shader_prog>(std::vector<std::pair<std::string, GLenum>>{std::make_pair(std::string(vertshader), GL_VERTEX_SHADER), std::make_pair(std::string(fragshader), GL_FRAGMENT_SHADER)},
                                     std::vector<std::pair<std::string, GLuint>>{std::make_pair(std::string("vert_pos"), GLuint(0))});

AAsset * font_asset = AAssetManager_open(asset_manager, "DejaVuSansMono.ttf", AASSET_MODE_STREAMING);
if(!font_asset)
    throw std::runtime_error("Couldn't open font asset");

std::vector<unsigned char> font_data;
while(true)
{
    std::vector<unsigned char> buffer(1024);
    auto size_read = AAsset_read(font_asset, std::data(buffer), std::size(buffer));
    if(size_read == 0)
        break;

    if(size_read == EOF)
        throw std::runtime_error("Error reading fonr asset");

    font_data.insert(std::end(font_data), std::begin(buffer), std::begin(buffer) + size_read);

    if(size_read < std::size(buffer))
        break;
}

__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "read %d bytes from font file", (int)std::size(font_data));
AAsset_close(font_asset);

font = std::make_unique<textogl::Font_sys>(font_data, 32);

glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
glViewport(0, 0, width, height);

__android_log_write(ANDROID_LOG_DEBUG, "DEBUG", "init success");
 */