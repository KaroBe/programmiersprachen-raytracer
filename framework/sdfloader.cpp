#include "sdfloader.hpp"


    Scene SDFloader::load(std::string const& inputFile)
    {
        Scene scene{};
        std::fstream input;
        input.open(inputFile);

        if(input.is_open())
        {
            std::string line;
            std::string word;
            
            while(std::getline(input, line))
            {   
                if(line.length() != 0)
                {
                    std::stringstream stream;
                    stream << line; 
                    stream >> word; 
                    if(word == "define")
                    {
                        stream >> word;

                        if(word == "material")
                        {
                            Material in_material;
                            
                            stream >> in_material.m_name;
                            stream >> in_material.m_ka.r;
                            stream >> in_material.m_ka.g;
                            stream >> in_material.m_ka.b;
                            stream >> in_material.m_kd.r;
                            stream >> in_material.m_kd.g;
                            stream >> in_material.m_kd.b;
                            stream >> in_material.m_ks.r;
                            stream >> in_material.m_ks.g;
                            stream >> in_material.m_ks.b;
                            stream >> in_material.m_m;
                            stream >> in_material.m_refrac;
                            stream >> in_material.m_opac;


                            //addToMaterial(material);
                            //scene.m_materials.push_back(in_material.m_name, in_material);
                            scene.m_materials[in_material.m_name] = in_material;
                            std::cout <<"Added material:\n" << in_material << std::endl;
                        }

                        else if(word == "shape")
                        {
                            stream >> word;
                            if(word == "box")
                            {   //find name min max etc. in sdf file
                                std::string name;
                                stream >> name;

                                glm::vec3 min;
                                stream >> min.x;
                                stream >> min.y;
                                stream >> min.z;

                                glm::vec3 max;
                                stream >> max.x;
                                stream >> max.y;
                                stream >> max.z;

                                std::string materialName;
                                stream >> materialName;
                                Material mat = scene.m_materials[materialName];

                                //construct box with min max etc. found earlier
                                auto boxptr = std::make_shared<Box>(name, mat, min, max);
                                scene.m_shapes.push_back(boxptr);
                                std::cout << "Added box:\n" << *boxptr << std::endl;

                                //Box in_box(name, mat, min, max);
                                //std::cout << "Added box:\n" << in_box <<std::endl;
                                //std::shared_ptr<Shape> p1(in_box);
                                //scene.m_shapes.push_back(std::make_shared<Shape>(in_box));
                            }
                            else if(word == "sphere")
                            {
                                std::string name;
                                stream >> name;

                                glm::vec3 center;
                                stream >> center.x;
                                stream >> center.y;
                                stream >> center.z;

                                float rad;
                                stream >> rad;

                                std::string materialName;
                                stream >> materialName;
                                Material mat = scene.m_materials[materialName];

                                //Sphere in_sphere(name, mat, center, rad);
                                //std::cout << "Added sphere:\n" << in_sphere <<std::endl;

                                auto sphereptr = std::make_shared<Sphere>(name, mat, center, rad);
                                scene.m_shapes.push_back(sphereptr);
                                std::cout << "Added sphere:\n" << *sphereptr << std::endl;
                            }

                            else if(word == "composite")
                            {
                                std::string comp_name;
                                stream >> comp_name;

                                //neues Composite anlegen
                                Composite new_comp(comp_name);
                                std::shared_ptr<Composite> comp_ptr = std::make_shared<Composite>(new_comp);

                                //add the new composite to the scene
                                scene.m_composite = comp_ptr;

                                //add shapes to the scene
                                while (!stream.eof())
                                {
                                    std::string shape_name;
                                    stream >> shape_name;

                                    // Shapes dem Composite hinzufügen:
                                    std::shared_ptr<Shape> found_shape;
                                    for (std::shared_ptr<Shape> s : scene.m_shapes)
                                    {
                                        if(s->get_name() == shape_name)
                                        {
                                            found_shape = s;
                                        }
                                    }
                                    if (!found_shape)
                                    {
                                        std::cout << "\nERROR shape not found";
                                    }
                                    else
                                    {
                                        scene.m_composite->add_shape(found_shape);
                                    }                                
                                }

                                scene.m_shapes.push_back(comp_ptr);

                                //Fertiges Composite ausgeben:
                                std::cout << "\nAdded composite: ~~~~~~~~~~~~\n" << *scene.m_composite << std::endl;
                                std::cout << "\n~~~~~~~~~~~~\n";

                            }

                        }
                        else if(word == "light")
                        {
                            std::string name;
                            stream >> name;

                            glm::vec3 position;
                            stream >> position.x;
                            stream >> position.y;
                            stream >> position.z;

                            Color color;
                            stream >> color.r;
                            stream >> color.g;
                            stream >> color.b;

                            float bright;
                            stream >> bright;

                            auto lightptr = std::make_shared<Light>(name, position, color, bright);
                            scene.m_lights.push_back(lightptr);
                            std::cout << "light added:\n" << *lightptr << std::endl;
                        }

                        else if(word == "camera")
                        {
                            std::string name;
                            stream >> name;

                            float fov_x;
                            stream >> fov_x;

                            glm::vec3 eye;
                            stream >> eye.x;
                            stream >> eye.y;
                            stream >> eye.z;

                            glm::vec3 dir;
                            stream >> dir.x;
                            stream >> dir.y;
                            stream >> dir.z;

                            glm::vec3 up;
                            stream >> up.x;
                            stream >> up.y;
                            stream >> up.z;

                            Camera camera(name, fov_x, eye, dir, up);
                            auto cameraptr = std::make_shared<Camera>(camera);
                            scene.m_camera = camera;
                            std::cout << "camera added:\n" << cameraptr << std::endl;
                        }

                    }
                    else if(word == "render")
                    {
                        std::string camname;
                        stream >> camname;

                        if(camname == scene.m_camera.get_name())
                        {
                            stream >> scene.m_fileOut;
                            stream >> scene.m_x_res;
                            stream >> scene.m_y_res;
                            std::cout << "rendering:\ncamera: " << camname << "\n" 
                                << "fileout: " << scene.m_fileOut << "\n"
                                << "x resolution: " << scene.m_x_res << "\n"
                                << "y resolution: " << scene.m_y_res << "\n";
                        }
                        else
                        {
                            std::cout << "camera not found" << std::endl;
                        }
                    }
                    else if(word == "ambient")
                    {
                        Color ambient;

                        stream >> ambient.r;
                        stream >> ambient.g;
                        stream >> ambient.b;

                        scene.m_ambient_light = ambient;
                        std::cout << "ambient light added: " << scene.m_ambient_light << std::endl;
                    }

                    else if(word == "transform")
                    {   
                        std::cout << "\ntranslating" << std::endl;
                        std::string object_name;
                        stream >> object_name;

                        // Shapes dem Composite hinzufügen:
                        std::shared_ptr<Shape> found_object;
                        for (std::shared_ptr<Shape> s : scene.m_shapes)
                        {
                            if(s->get_name() == object_name)
                            {
                                found_object = s;
                                std::cout << "found object: " << object_name << std::endl;
                            }
                        }
                        stream >> word;
                        if (!found_object)
                        {
                            if(object_name == scene.m_camera.get_name())
                            {
                                if(word == "translate")
                                {
                                    glm::vec3 vector;
                                    stream >> vector.x;
                                    stream >> vector.y;
                                    stream >> vector.z;

                                    scene.m_camera.translate(vector);
                                }
                                else if(word == "rotate")
                                {
                                    float angle;
                                    stream >> angle;
                                    glm::vec3 vector;
                                    stream >> vector.x;
                                    stream >> vector.y;
                                    stream >> vector.z;

                                    scene.m_camera.rotate(angle, vector);
                                }
                                else if(word == "scale")
                                {
                                    /*glm::vec3 value;
                                    stream << value.x;
                                    stream << value.y;
                                    stream << value.z;

                                    //scene.m_camera.scale(value);*/
                                    std::cout << "\nCan't scale camera, try messing with the fov_x and resolution.";
                                }
                            }
                            else
                            {
                                std::cout << "\nERROR object not found";
                            }
                        }
                        else //if object is a shape
                        {
                            if(word == "translate")
                            {
                                glm::vec3 vector;
                                stream >> vector.x;
                                stream >> vector.y;
                                stream >> vector.z;
                                std::cout << "translating " << object_name << std::endl;
                                found_object -> translate(vector);
                            }
                            else if(word == "rotate")
                            {
                                float angle;
                                stream >> angle;
                                glm::vec3 vector;
                                stream >> vector.x;
                                stream >> vector.y;
                                stream >> vector.z;
                                std::cout << "rotating " << object_name << std::endl;
                                found_object -> rotate(angle, vector);
                            }
                            else if(word == "scale")
                            {
                                glm::vec3 value;
                                stream << value.x;
                                stream << value.y;
                                stream << value.z;
                                std::cout << "scaling " << object_name << std::endl;
                                found_object -> scale(value);
                            }
                        } 
                    }

                } //endif length != 0
            
            } //end while getline()

            std::cout << "\nSDF-loading done. This is the structure of your scene: \n";
            std::cout << *scene.m_composite;
            return scene;
        }
        else
        {
            std::cout << "Couldn't find file. Empty Scene returned!" << std::endl;
            return scene;
        }
    }
    

