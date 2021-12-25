CREATE TABLE SensorData (
id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
sensor VARCHAR(30) NOT NULL,
location VARCHAR(30) NOT NULL,
temp VARCHAR(10),
humid VARCHAR(10),
reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)