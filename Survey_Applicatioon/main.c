#include <gtk/gtk.h>
#define MAX_LENGTH 100

typedef struct {
    char name[MAX_LENGTH];
    char course[MAX_LENGTH];
    char section[MAX_LENGTH];
    int year;
    int responses[5];
} SurveyResponse;

GtkWidget *window;
GtkWidget *nameEntry;
GtkWidget *courseEntry;
GtkWidget *sectionEntry;
GtkWidget *yearSpin;
GtkWidget *responses[5];

// Submit button callback
void on_submit_button_clicked(GtkWidget *widget, gpointer data)
{
    SurveyResponse response;
    strcpy(response.name, gtk_entry_get_text(GTK_ENTRY(nameEntry)));
    strcpy(response.course, gtk_entry_get_text(GTK_ENTRY(courseEntry)));
    strcpy(response.section, gtk_entry_get_text(GTK_ENTRY(sectionEntry)));
    response.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yearSpin));

    // Store the responses
    for (int i = 0; i < 5; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(responses[i])))
            response.responses[i] = 1;
        else
            response.responses[i] = 0;
    }

    // Process the survey response (e.g., store in a file or database)

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Response Submitted");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_widget_destroy(window);
}

// Create the survey GUI
void create_survey_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Survey Questionnaire");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Name entry
    GtkWidget *nameLabel = gtk_label_new("Name:");
    gtk_box_pack_start(GTK_BOX(vbox), nameLabel, FALSE, FALSE, 0);
    nameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Enter your name");  // Set placeholder text
    gtk_box_pack_start(GTK_BOX(vbox), nameEntry, FALSE, FALSE, 0);

    // Course entry
    GtkWidget *courseLabel = gtk_label_new("Course:");
    gtk_box_pack_start(GTK_BOX(vbox), courseLabel, FALSE, FALSE, 0);
    courseEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(courseEntry), "Enter your course");  // Set placeholder text
    gtk_box_pack_start(GTK_BOX(vbox), courseEntry, FALSE, FALSE, 0);

    // Section entry
    GtkWidget *sectionLabel = gtk_label_new("Section:");
    gtk_box_pack_start(GTK_BOX(vbox), sectionLabel, FALSE, FALSE, 0);
    sectionEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(sectionEntry), "Enter your section");  // Set placeholder text
    gtk_box_pack_start(GTK_BOX(vbox), sectionEntry, FALSE, FALSE, 0);

    // Survey questions
    GtkWidget *questionsLabel = gtk_label_new("Survey Questions:");
    gtk_box_pack_start(GTK_BOX(vbox), questionsLabel, FALSE, FALSE, 10);

    for (int i = 0; i < 5; i++) {
        GtkWidget *questionLabel = gtk_label_new(NULL);
        switch (i) {
            case 0:
                gtk_label_set_text(GTK_LABEL(questionLabel), "1. Do you agree or disagree with the statement: \"Artificial intelligence will lead to widespread job displacement and unemployment\"?");
                break;
            case 1:
                gtk_label_set_text(GTK_LABEL(questionLabel), "2. Do you agree or disagree with the statement: \"Cryptocurrency will eventually replace traditional forms of currency\"?");
                break;
            case 2:
                gtk_label_set_text(GTK_LABEL(questionLabel), "3. Do you agree or disagree with the statement: \"Virtual reality technology has the potential to revolutionize entertainment and gaming\"?");
                break;
            case 3:
                gtk_label_set_text(GTK_LABEL(questionLabel), "4. Do you agree or disagree with the statement: \"Smart devices and Internet of Things (IoT) have improved our daily lives\"?");
                break;
            case 4:
                gtk_label_set_text(GTK_LABEL(questionLabel), "5. Do you agree or disagree with the statement: \"Social media platforms should have stricter regulations to protect user privacy and combat misinformation\"?");
                break;
        }

        gtk_box_pack_start(GTK_BOX(vbox), questionLabel, FALSE, FALSE, 5);

        GtkWidget *radioButtonAgree = gtk_radio_button_new_with_label(NULL, "Agree");
        gtk_box_pack_start(GTK_BOX(vbox), radioButtonAgree, FALSE, FALSE, 0);

        GtkWidget *radioButtonDisagree = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioButtonAgree), "Disagree");
        gtk_box_pack_start(GTK_BOX(vbox), radioButtonDisagree, FALSE, FALSE, 0);

        responses[i] = radioButtonAgree;
    }

    // Submit button
    GtkWidget *submitButton = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(vbox), submitButton, FALSE, FALSE, 10);
    g_signal_connect(submitButton, "clicked", G_CALLBACK(on_submit_button_clicked), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK+ main loop
    gtk_main();
}

int main(int argc, char *argv[]) {
    create_survey_gui(argc, argv);
    return 0;
}
