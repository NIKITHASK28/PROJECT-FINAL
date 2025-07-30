import streamlit as st
import sqlite3
import random
from styles import profile, letterprogress

st.markdown(profile(), unsafe_allow_html=True)
st.markdown(letterprogress(), unsafe_allow_html=True)

# Check if 'page' exists in session state, if not, initialize it
if "page" not in st.session_state:
    st.session_state["page"] = "profilepage"

st.session_state["page"] = "profilepage"

# Connect to the SQLite database
conn = sqlite3.connect("signlingo.db")

# Create a cursor object
cursor = conn.cursor()

# Retrieve current user information from session state
current_user = st.session_state["current_user"]

title = f"""
<div class="welcome-content">Hello {current_user['name'].title()}, Welcome Back!</div>
<div class="my_course_title">
    <h1>Food Recommendations</h1>
</div>
"""
st.markdown(title, unsafe_allow_html=True)

# Food Recommendations (Example, you can customize it as per your needs)
food_recommendations = [
    "Sambar with brown rice and a side of steamed vegetables",
    "Ragi mudde (finger millet ball) with vegetable sambar",
    "Pongal made with millets, served with coconut chutney",
    "Thayir sadam (curd rice) with a side of pickle and salad",
    "Kootu (vegetable and lentil curry) with brown rice",
    "Adai (spicy lentil pancakes) with chutney",
    "Chapati with vegetable kurma",
    "Murungai keerai (drumstick leaves) soup",
    "Sundal (spicy chickpea salad) made with coconut",
    "Moru curry (buttermilk curry) with steamed rice"
]
# Randomly select a food recommendation
recommended_food = random.choice(food_recommendations)

# Display food recommendation
col1, col2 = st.columns([0.5, 0.5])

with col1:
    st.subheader("Today's Food Suggestion")
    st.write(f"**{recommended_food}**")

# Optionally, you can add some images for the food recommendations (example placeholder image URLs)
food_images = {
    "Sambar with brown rice and a side of steamed vegetables": "https://www.example.com/sambar-brown-rice.jpg",
    "Ragi mudde (finger millet ball) with vegetable sambar": "https://www.example.com/ragi-mudde.jpg",
    "Pongal made with millets, served with coconut chutney": "https://www.example.com/pongal.jpg",
    "Thayir sadam (curd rice) with a side of pickle and salad": "https://www.example.com/thayir-sadam.jpg",
    "Kootu (vegetable and lentil curry) with brown rice": "https://www.example.com/kootu-brown-rice.jpg",
    "Adai (spicy lentil pancakes) with chutney": "https://www.example.com/adai.jpg",
    "Chapati with vegetable kurma": "https://www.example.com/chapati-vegetable-kurma.jpg",
    "Murungai keerai (drumstick leaves) soup": "https://www.example.com/murungai-keerai-soup.jpg",
    "Sundal (spicy chickpea salad) made with coconut": "https://www.example.com/sundal.jpg",
    "Moru curry (buttermilk curry) with steamed rice": "https://www.example.com/moru-curry.jpg"
}

# Show the image corresponding to the recommended food
food_name = recommended_food.split()[0]  # Get the first word to match the food name (e.g., "Pizza")
image_url = food_images.get(food_name, "")

with col2:
    if image_url:
        st.image(image_url, use_column_width=True)
