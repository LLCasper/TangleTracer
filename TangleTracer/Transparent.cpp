// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Transparent.h"

// ---------------------------------------------------------------- default constructor

Transparent::Transparent (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular),
		specular_btdf(new PerfectTransmitter)
{}



// ---------------------------------------------------------------- copy constructor

Transparent::Transparent(const Transparent& m)
	: 	Phong(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;

	if(m.specular_brdf)
		specular_brdf = m.specular_brdf->clone(); 
	else  specular_brdf = NULL;

	if(m.specular_btdf)
		specular_btdf = m.specular_btdf->clone(); 
	else  specular_btdf = NULL;

	if(m.reflective_brdf)
		reflective_brdf = m.reflective_brdf->clone(); 
	else  reflective_brdf = NULL;
}


// ---------------------------------------------------------------- clone

Material*										
Transparent::clone(void) const {
	return (new Transparent(*this));
}	


// ---------------------------------------------------------------- assignment operator

Transparent& 
Transparent::operator= (const Transparent& rhs) {
	if (this == &rhs)
		return (*this);
		
	Material::operator=(rhs);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
		
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if (rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();

	if (rhs.reflective_brdf)
		this->reflective_brdf = rhs.reflective_brdf->clone();

	if (rhs.specular_btdf)
		this->specular_btdf = rhs.specular_btdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Transparent::~Transparent(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBColor
Transparent::shade(ShadeRec& sr) {
		/*
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);    
		float 		ndotwi 	= sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;

			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if (!in_shadow) 
				L += (	diffuse_brdf->f(sr, wo, wi) 
						  + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
		}
	}
	return (L);*/

	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);

	if(specular_btdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1);
	else {
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr*sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1)*fabs(sr.normal*wi);

		L += ft*sr.w.tracer_ptr->trace_ray(transmitted_ray,sr.depth+1)*fabs(sr.normal*wt);		//this is very important for transparent rendering
	}

	return (L);
}

	
RGBColor
Transparent::area_light_shade(ShadeRec& sr)			//this is for chapter 18 page one image ad-hoc
{
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);    
		float 		ndotwi 	= sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;

			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if (!in_shadow) 
				L += (	diffuse_brdf->f(sr, wo, wi) 
						  + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi * sr.w.lights[j]->G(sr) / sr.w.lights[j]->pdf(sr);
		}
	}
	return (L);
}
