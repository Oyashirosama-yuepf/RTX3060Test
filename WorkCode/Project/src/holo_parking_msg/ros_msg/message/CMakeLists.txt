find_package(catkin REQUIRED COMPONENTS message_generation genmsg)

add_message_files(DIRECTORY vision)
add_message_files(DIRECTORY planning)
add_message_files(DIRECTORY control)
add_message_files(DIRECTORY localization)

generate_messages(DEPENDENCIES)

