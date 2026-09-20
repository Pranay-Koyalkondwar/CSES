import numpy as np
import matplotlib.pyplot as plt

# --- Parameters ---
# Physical parameters
nu = 1e-4        # Kinematic viscosity (m^2/s)
omega = 2 * np.pi # Angular frequency (rad/s), T = 1 second
u0 = 1.0         # Amplitude of plate velocity (m/s)

# Derived parameters
delta = np.sqrt(2 * nu / omega)  # Penetration depth
Period = 2 * np.pi / omega

# Domain parameters
H = 6 * delta    # Plot up to 6 times the penetration depth to show decay
y = np.linspace(0, H, 500)

# --- Time Snapshots ---
# Plot at 0, T/4, T/2, 3T/4 to show a full cycle evolution
times = [0, Period/4, Period/2, 3*Period/4]
labels = ['t = 0', 't = T/4', 't = T/2', 't = 3T/4']

# --- Plotting ---
plt.figure(figsize=(8, 10))

# 1. Plot the exponential envelope (boundaries)
u_envelope = u0 * np.exp(-y / delta)
plt.plot(u_envelope, y, 'k--', linewidth=1.5, alpha=0.5, label='Envelope $\pm u_0 e^{-y/\delta}$')
plt.plot(-u_envelope, y, 'k--', linewidth=1.5, alpha=0.5)

# 2. Plot velocity profiles at different times
for i, t in enumerate(times):
    # Stokes solution: u(y,t) = u0 * exp(-y/delta) * cos(omega*t - y/delta)
    u = u0 * np.exp(-y / delta) * np.cos(omega * t - y / delta)
    plt.plot(u, y, linewidth=2, label=labels[i])

# Formatting
plt.title("Stokes' Second Problem: Oscillating Plate Velocity Profiles", fontsize=14)
plt.xlabel("Velocity u (m/s)", fontsize=12)
plt.ylabel("Distance from plate y (m)", fontsize=12)
plt.xlim(-u0 * 1.1, u0 * 1.1) # Set x-axis to show negative and positive swing
plt.ylim(0, H)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=10)

# Add annotation for penetration depth
plt.axhline(y=delta, color='r', linestyle=':', alpha=0.7)
plt.text(u0*0.6, delta*1.05, r'Penetration Depth $\delta$', color='r')

plt.tight_layout()
plt.show()