#version 430 core
layout(points) in;
layout(triangle_strip, max_vertices = 14) out;//(_seg_num +1)*2w

uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform int  _seg_num = 6;
uniform vec2 _wheat_root_of_tex;
uniform vec2 _tex_size;
in block1
{
	vec3 _color;
	vec3 _angle;
	vec3 _swing;
} _in[1];

out vec2 _texCoord;
out float _dist_to_eye;
out vec4 _color;

vec2 coords[4] = vec2[4]( 
	vec2(0.0, 1.0),
	vec2(1.0, 1.0),
	vec2(0.0, 0.0),
	vec2(1.0, 0.0)
);
vec3 vertice[4]= vec3[4]( 
	vec3(0,0,0),
	vec3(_tex_size.x,0,0),
	vec3( 0,_tex_size.y,0),
	vec3(_tex_size.xy,0)
);
vec4 emit_vertex[2]=vec4[2](
		vec4(0.0        , 0.0, 0.0, 1.0),
		vec4(_tex_size.x, 0.0, 0.0, 1.0)
	);
vec3 _eye;

mat4 makeRotationMatrix(vec4 axis)
{	
	mat4 w=mat4(0.0);
	w[0][1] =  axis.z;
	w[0][2] = -axis.y;
	w[1][0] = -axis.z;
	w[1][2] =  axis.x;
	w[2][0] =  axis.y;
	w[2][1] = -axis.x;
	return mat4(1.0)+w*sin(axis.w)+w*w*(1-cos(axis.w));
}
mat4 makeRotationMatrix(float theta,vec3 axis)
{
	return makeRotationMatrix(vec4(axis,theta));
}

vec4 getAxisTheta(vec3 cross_vec)
{
	float theta = asin(length(cross_vec));
	if(theta == 0)
		return vec4(vec3(1,0,0),theta);
	else		
		return vec4(normalize(cross_vec),theta);
}
mat4 makeRotationMatrixByCrossedVector(vec3 cross_vec)
{
	vec4 axis_theta=getAxisTheta(cross_vec);
	return makeRotationMatrix(axis_theta);
}

mat4 makeTranslationMatrix(vec3 t)
{
	mat4 result=mat4(1.0);
	result[3]=vec4(t,1.0);
	
	return result;
}
mat4 getBillBoardMatrix()
{	
	vec3 v=_eye-gl_in[0].gl_Position.xyz;
	v.y=0.0;
	v=normalize(v);	
	vec3 n=vec3(0.0, 0.0, 1.0);
	float theta=acos(dot(n,v));
	float sign=normalize(cross(n,v)).y;
	return makeRotationMatrix(sign*theta,vec3(0,1,0));
}
mat4 getRootTranslationMatrix()
{
	mat4 root_mat=mat4(1.0);
	root_mat[3]=  vec4(-_wheat_root_of_tex.x,_wheat_root_of_tex.y-_tex_size.y,0,1);	
	return root_mat;
}
mat4 getSegmentRotateMatrix(vec3 crossed)
{
	vec4 axis_theta=getAxisTheta(crossed);
	axis_theta.w /= float(_seg_num);
	return makeRotationMatrix(axis_theta);
}
mat4 quick_inverse(mat4 m)
{
	mat4 result=m;
	vec4 t=m[3];
	result[3]=vec4(0.0, 0.0, 0.0, 1.0);
	result = transpose(result);
	result[3]=-result*t;
	return result;
}
void main(void)
{	
	_eye=quick_inverse(modelViewMatrix)[3].xyz;	
	mat4 root_rotate    = makeRotationMatrixByCrossedVector(_in[0]._angle);
	mat4 bill_board_mat = getBillBoardMatrix();
	mat4 root_tex_trans = getRootTranslationMatrix();
	
	float seg_height     = _tex_size.y / float(_seg_num);
	float seg_tex_height = 1.0         / float(_seg_num);
	mat4  seg_swing_mat  = getSegmentRotateMatrix(_in[0]._swing);
	mat4  pos_mat   = makeTranslationMatrix(gl_in[0].gl_Position.xyz);
	
	mat4 wheat_mat      = bill_board_mat * root_tex_trans;
	mat4 seg_grow_mat   = makeTranslationMatrix(vec3(0,seg_height,0));
	mat4 seg_rotate_mat = seg_swing_mat;
	mat4 grow_mat       = seg_rotate_mat * root_rotate * seg_grow_mat;
	for(int i=0;i<=_seg_num;i++)
	{		
		float th = float(i)*seg_tex_height;
		vec2 emit_coord[2]=vec2[2](
			vec2(0.0, 1.0-th),
			vec2(1.0, 1.0-th)
		);

		for(int j=0;j<2;j++)
		{
			vec4 new_vertex = pos_mat * wheat_mat * emit_vertex[j];
			gl_Position   = modelViewProjectionMatrix*new_vertex;
			_color = vec4(_in[0]._color,1);
			_texCoord     = emit_coord[j];
			_dist_to_eye  = length(new_vertex.xyz-_eye);
			EmitVertex();
		}
		pos_mat  = pos_mat * grow_mat;
		grow_mat = seg_rotate_mat * seg_grow_mat;
	}
	EndPrimitive();
}