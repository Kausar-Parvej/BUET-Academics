module com.example.java_term_project_part_two {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.client to javafx.fxml;
    exports com.example.client;
    exports my_util;
    exports server;
}