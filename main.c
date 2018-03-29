#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "src/oauth.h"

//
// Created by ishibkikh on 3/27/2018.
//

int main()
{
    char * i_url = "https://qap.api.wiley.com/wpng/lti/v1/orion/EPROF10808/target/CH_3";
    char * i_method = "POST";
    char * i_params = "context_id=2013ce61eb2c81542ef8456b4084e2828e3ae429&context_label=WPNG%2010e&context_title=WPNG%20Perf%20integration%20Test%3A%20Halliday%2C%20Physics%2C%2010e&custom_canvas_api_domain=wiley2.instructure.com&custom_canvas_course_id=11615&custom_canvas_enrollment_state=active&custom_canvas_user_id=2434&custom_canvas_user_login_id=canvas_wpng-perf-stud1000%40wiley.com&custom_canvas_workflow_state=available&custom_domain_id=2&ext_roles=urn%3Alti%3Ainstrole%3Aims%2Flis%2FAdministrator%2Curn%3Alti%3Ainstrole%3Aims%2Flis%2FInstructor%2Curn%3Alti%3Asysrole%3Aims%2Flis%2FUser&launch_presentation_document_target=iframe&launch_presentation_locale=en&launch_presentation_return_url=https%3A%2F%2Fwiley2.instructure.com%2Fcourses%2F11615%2Fexternal_content%2Fsuccess%2Fexternal_tool_redirect&lis_person_contact_email_primary=canvas_wpng-perf-stud1000%40wiley.com&lis_person_name_family=sname1000&lis_person_name_full=name1000%20sname1000&lis_person_name_given=name1000&lis_person_sourcedid=canvas_wpng-perf-stud1000%40wiley.com&lti_message_type=basic-lti-launch-request&lti_version=LTI-1p0&resource_link_id=9564c847865a8c6787934ca042f02cfe45cc0858&resource_link_title=https%3A%2F%2Fqap.api.wiley.com%2Fwpng%2Flti%2Fv1%2Forion%2FEPROF10808%2Ftarget%2Fhome&roles=Learner&tool_consumer_info_product_family_code=canvas&tool_consumer_info_version=cloud&tool_consumer_instance_contact_email=notifications%40instructure.com&tool_consumer_instance_guid=1lfEyYQuYWx7YVykDzrtjzB4BUXEw7NEZgmX2tiZ%3Acanvas-lms&tool_consumer_instance_name=Wiley%20Account&user_id=e0a7461a09486441053112bcd3d9e5348f14043b";
    //char * i_params = "context_id=2013ce61eb2c81542ef8456b4084e2828e3ae429&user_id=e0a7461a09486441053112bcd3d9e5348f14043b";
    char * i_consumer_key = "harness";
    char * i_consumer_secret = "secret_wiley";

    char * oauth_nonce = "UhZu9oHskwYa3FdvLPvASLbjIFoxvbDj";
    char * oauth_timestamp = "1522157349";

    char * expected_signature = "yq4akc9tERx796%2B9oK5LXB2Q7BU%3D";

    char * signed_body = oauth_sign_post(i_url, i_params, i_consumer_key, i_consumer_secret);
    printf("%s\n", signed_body);
    free(signed_body);

    printf("\n\nSUCCESS\n");
    return 0;
}
