#version 450 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

uniform int channel;        // Image filter channel
uniform vec3 modifier;      // Modifier
uniform vec3 resolution;    // Resolution of window

void main()
{
    color = texture(ourTexture1, TexCoord);
    float grayScale = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;

    if((channel & 1) != 0)
    {
        color = vec4(color.r, 0, 0, 1);
    }
    if((channel & 2) != 0)
    {
        color = vec4(0, color.g, 0, 1);
    }
    if((channel & 4) != 0)
    {
        color = vec4(0,0,color.b,1);
    }
    if((channel & 8) != 0)
    {
        color = vec4(grayScale, grayScale, grayScale, 1);
    }
    if((channel & 16) != 0)
    {
        color = vec4(color.r + modifier.r, color.g + modifier.g, color.b + modifier.b, 1);
    }
    if((channel & 32) != 0)
    {
        color = vec4(1 - color.r, 1 - color.g, 1 - color.b, 1);
    }
    if((channel & 64) != 0)
    {
        if(grayScale < 0.5f)
        {
            color = vec4(0,0,0,1);
        }
        else
        {
            color = vec4(1,1,1,1);
        }
    }
    if((channel & 128) != 0)
    {
        ////Dark Purple :3
        //color = vec4(color.r/2, 0, color.b/2, 1);
        //If pixel is too dark, turn into white.
        if(grayScale < 0.12)
        {
            color = vec4(1,1,1,1);
        }
    }
    if((channel & 256) != 0)
    {
        if((color.r + color.g + color.b)/3 > 0.99)
        {
            color = vec4(1,0,0,1);
        }
    }
    if((channel & 512) != 0)
    {
        if((color.r + color.g + color.b)/3 > 0.99)
        {
            color = vec4(0,1,0,1);
        }
    }
    if((channel & 1024) != 0)
    {
        if((color.r + color.g + color.b)/3 > 0.99)
        {
            color = vec4(0,0,1,1);
        }
    }
    if((channel & 2048) != 0)
    {
        if((color.b > color.r * 1.1))
        {
            color = vec4(color.r, color.g, 1 - color.b, 1);
        }
    }
    if((channel & 4096) != 0)
    {
        color = vec4(color.r, color.g, 0, 1);
    }
    if((channel & (2 << 12)) != 0)
    {
        color = vec4(color.r, 0, color.b, 1);
    }
    if((channel & (2 << 13)) != 0)
    {
        color = vec4(0, color.g, color.b, 1);
    }
    if((channel & (2 << 14)) != 0)
    {
        color = vec4(color.r, color.g/2, 0, 1);
    }
}