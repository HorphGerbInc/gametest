pipeline {

    agent {label 'Linux'}

    stages {

        stage('Setup') {
            sh 'apt-get install cmake; apt-get install build-essential'
        }

        stage('Build') {

            steps {
                checkout scm
                sh 'mkdir build; cd build; cmake ..; make'    
            }

        }

    }

}
