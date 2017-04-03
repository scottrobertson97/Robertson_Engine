#version 430
uniform vec2 WindowSize;
void main()
{
	float x = gl_FragCoord.x / WindowSize.x * 0.9 + 0.05;
	float y = gl_FragCoord.y / WindowSize.y * 0.9 + 0.05;
	float avg = ((0.9-x)+(0.9-y))/2;
	gl_FragColor = vec4(x,avg,y,1);
}