#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform int  _seg_num;
uniform vec2 _wheat_root_of_tex;
uniform vec2 _tex_size;
uniform vec2 _tu;

varying in  vec3 _color[1];
varying in  vec3 _angle[1];
varying in  vec3 _swing[1];
varying in  vec3 _touch[1];

varying out vec2 _texCoord;
varying out float _dist_to_eye;

vec2 coords[4] = vec2[4]( 
	vec2(0.0  ,_tu.y),
	_tu.xy,
	vec2(0.0  ,0.0  ),
	vec2(_tu.x,0.0  )
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
	result[3].xyz=t;
	return result;
}
mat4 getBillBoardMatrix()
{	
	vec3 v=_eye-gl_PositionIn[0].xyz;
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
	root_mat[3].xy= - vec2(_wheat_root_of_tex.x,_tex_size.y-_wheat_root_of_tex.y);
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
	result=transpose(result);
	result[3]=-result*t;
	return result;
}
void main(void)
{	
	_eye=quick_inverse(gl_ModelViewMatrix)[3].xyz;	
	mat4 root_rotate    = makeRotationMatrixByCrossedVector(_angle[0]);
	mat4 bill_board_mat = getBillBoardMatrix();
	mat4 root_tex_trans = getRootTranslationMatrix();
	
	vec4 touch_axis_theta=getAxisTheta(_touch[0]);
	touch_axis_theta.w /= float(_seg_num);

	float seg_height     = _tex_size.y / float(_seg_num);
	float seg_tex_height = _tu.y       / float(_seg_num);
	mat4  seg_swing_mat  = getSegmentRotateMatrix(_swing[0]);
	mat4  seg_touch_mat  = getSegmentRotateMatrix(_touch[0]);
	mat4  pos_mat   = makeTranslationMatrix(gl_PositionIn[0].xyz);
	
	
	mat4 wheat_mat      = bill_board_mat * root_tex_trans;
	mat4 seg_grow_mat   = makeTranslationMatrix(vec3(0,seg_height,0));
	mat4 seg_rotate_mat = seg_touch_mat * seg_swing_mat;
	mat4 grow_mat       = seg_rotate_mat * root_rotate * seg_grow_mat;
	for(int i=0;i<=_seg_num;i++)
	{		
		float th = float(i)*seg_tex_height;
		vec2 emit_coord[2]=vec2[2](
			vec2(0.0  , 1.0-th),
			vec2(_tu.x, 1.0-th)
		);

		for(int j=0;j<2;j++)
		{
			vec4 new_vertex = pos_mat * wheat_mat * emit_vertex[j];
			gl_Position   = gl_ModelViewProjectionMatrix*new_vertex;
			gl_FrontColor = vec4(_color[0],1);
			_texCoord     = emit_coord[j];
			_dist_to_eye  = length(new_vertex.xyz-_eye);
			EmitVertex();
		}
		pos_mat  = pos_mat * grow_mat;
		grow_mat = seg_rotate_mat * seg_grow_mat;
	}
	EndPrimitive();	
}