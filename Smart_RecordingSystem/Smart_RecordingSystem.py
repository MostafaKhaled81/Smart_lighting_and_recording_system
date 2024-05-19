import cv2
import pytesseract
import pandas as pd
from datetime import datetime
import time  # Import the time module for adding delay
# Set the path to the Tesseract executable (modify accordingly based on your installation)
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

def extract_text_from_image_and_save_to_excel():
    # Open the camera (camera index 0 is usually the default webcam)
    cap = cv2.VideoCapture(0)

    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Display the frame
        cv2.imshow('Camera', frame)

        # Press 'q' to exit the loop
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Convert the frame to grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Use Tesseract OCR to extract text
        car_plate = pytesseract.image_to_string(gray,lang='eng')

        # If text is detected, save to Excel
        if car_plate.strip():
            # Print the extracted text
            print("Extracted Text:", car_plate)

            # Get the current date and time of the PC
            current_datetime = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

            # Create a DataFrame for the new data
            new_data = {'DateTime': [current_datetime], 'car_num': [car_plate]}
            df_new = pd.DataFrame(new_data)

            # Try to load an existing Excel file, or create a new one if it doesn't exist
            try:
                df_existing = pd.read_excel('output.xlsx', sheet_name='Sheet1')
            except FileNotFoundError:
                df_existing = pd.DataFrame()

            # Concatenate the existing DataFrame with the new data
            df_combined = pd.concat([df_existing, df_new], ignore_index=True)

            # Save the combined DataFrame to an Excel file
            df_combined.to_excel('output.xlsx', sheet_name='Sheet1', index=False)

            print("Data saved to 'output.xlsx'")
            #for wait in range(10):
                #print("wait")
#OR 
            # Add a delay to avoid high CPU usage
            time.sleep(1)
    # Release the camera and close the OpenCV window
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    extract_text_from_image_and_save_to_excel()
