pipeline {

    agent {label 'Linux'}

    stages {

        stage('Build') {

            steps {
                checkout scm
                sh 'mkdir build; cd build; cmake ..; make'    
            }

        }

        stage('Test') {
            steps {
                sh 'cd build; make test'
            }
        }

    }

}
