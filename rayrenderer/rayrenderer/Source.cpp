#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "util_helpers.h"
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.get_direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	auto lerp = (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

	return lerp;
}

int main() {

	//set image parameters
	int output_width = 800;
	auto aspect_ratio = 16.0 / 9.0;
	int output_height = static_cast<int>(output_width / aspect_ratio);
	output_height = (output_height < 1) ? 1 : output_height;
	int channels = 4;

	//size of the image in terms of memory required
	size_t img_size = output_width * output_height * channels;
	unsigned char* img = new unsigned char[img_size];

	//World
	hittable_list world;

	world.add(make_shared<sphere>(point3(0, -100.5, -5.5), 100));
	world.add(make_shared<sphere>(point3(0, 0, -1.5), 0.5));

	//set camera parameters
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(output_width)/output_height);
	auto focal_length = 1.0;
	auto camera_center = point3(0, 0, 0);

	//vectors for ray alignment and spacing
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	auto pixel_delta_u = viewport_u / output_width;
	auto pixel_delta_v = viewport_v / output_height;

	auto upper_left_pixel = camera_center - vec3(0,0,focal_length) - (0.5*viewport_u) - (0.5*viewport_v);
	auto pixel00_loc = upper_left_pixel + (0.5 * (pixel_delta_u + pixel_delta_v));



	//rendering the image pixel by pixel
	unsigned char* p = img;
	for (int j = 0; j < output_height; j++) {
		for (int i = 0; i < output_width; i++, p += channels) {
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(pixel_center, ray_direction);

			color pixel_color = ray_color(r, world);

			write_color(p, pixel_color, 255);
		}
		//std::cout << "Scanlines remaining: " << (output_height - j) << '\n';
	}

	stbi_write_png("C:/Users/neeli/OneDrive/Desktop/base.png", output_width, output_height, channels, img, output_width*channels);

	stbi_image_free(img);

	return 0;
}