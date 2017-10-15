pipeline {

    agent {label 'Linux_OpenGL'}

    stages {

        stage('Build') {

            steps {
                checkout scm
                sh 'mkdir -p build; cd build; cmake ..; make'    
            }

        }

        stage('Test') {
            steps {
                sh 'cd build; ctest -V'
            }
        }

        stage('Cleanup') {
            steps {
                sh 'rm -r build'
            }
        }

    }

}
