------------------------------
## 🚀 Raspberry Pi Home Cloud Server Architecture & Setup Guide
Comprehensive architectural documentation and step-by-step implementation logs for building a secure, automated personal home cloud storage and management system using a Raspberry Pi, dual storage drives, CasaOS, and Cloudflare Zero Trust Tunnels.
------------------------------
## 🗺️ Architectural System Overview
The system architecture is designed to bypass common consumer ISP restrictions (such as Carrier-Grade NAT and blocked inbound ports) while maintaining enterprise-grade security parameters:

🌐 Public Internet (User)
       │
       ▼ [HTTPS / TLS 1.3 Encryption]
☁️ Cloudflare Edge Network (derrildsouza.com)
       │
       ▼ [Secure Outbound Encrypted Tunnel Client connection]
📶 Home Gateway Router (Airtel Nokia - Port Forwarding Closed)
       │
       ▼ [Internal loopback port forwarding via cloudflared]
🍓 Raspberry Pi Core Architecture (Debian Bookworm OS Node)
       ├─ 🐳 CasaOS Engine Orchestrator [Localhost Port 80 Bridge]
       └─ 💾 Storage Array Architecture [/etc/fstab Sequential Array Array Array]
            └─ 💽 storage1_320g (NTFS Dual-Platform Dynamic Volume Node)

------------------------------
## 🛠️ Infrastructure Core Prerequisites

* Hardware Unit: Raspberry Pi single-board computer running a 64-bit architecture distribution (Debian Bookworm OS Node).
* Storage Arrays: 1× External 2.5" Mechanical HDD (320 GB capacity profile).
* Network Components: Active public domain registration (derrildsouza.com) hosted under a Cloudflare site profile.
* Orchestration Dashboard: CasaOS environment deployed locally.

------------------------------
## 💾 Phase 1: Dual-Platform System Storage Configuration
To ensure maximum interoperability, external hard disks are provisioned using the NTFS file system matrix. This lets the hardware move seamlessly between native Windows host machines and the headless Raspberry Pi Linux environment.
## 1. Drive Geometry & Partition Alignment Fixes
When moving a drive initialized in virtualized hypervisors over to the physical Raspberry Pi USB bus tracks, sector geometry discrepancies can occur.
Open the partition configuration utility console natively to review the array mappings:

sudo parted /dev/sda

The application will scan block parameters, catch misaligned sector allocation arrays, and throw a boundary alert layout sequence. Execute the inline repair hook immediately:

* Warning Prompt Detected: Warning: Not all of the space available to /dev/sda appears to be used... Fix/Ignore?
* Interactive Parameter Input: Type Fix and hit Enter.
* Exit Routine: Type quit and hit Enter.

## 2. Resolving Windows Fast Startup & Unclean Journal Locks
If a drive is pulled from a Windows machine with Fast Startup active, the internal NTFS filesystem journal flags are marked as dirty. This blocks write execution layers inside Linux.
Execute a low-level volume repair and clear the active hibernation lock tracks:

sudo ntfsfix /dev/sda1

Override remaining safety validation flags to force-inject your permanent size-descriptive asset tag tracking label structure:

sudo ntfslabel --force /dev/sda1 "Derril_bckp1_23-May-2026"

Verify that your volume headers, file attributes, and block mappings are cleanly registered:

sudo blkid /dev/sda1

Expected Output Parameters:

/dev/sda1: LABEL="Derril_bckp1_23-May-2026" BLOCK_SIZE="512" UUID="6F725C1264FDAFD4" TYPE="ntfs" PARTLABEL="primary"

## 3. Implementing Automated Boot Mount Structures (fstab via Vim)
To ensure future expansion capability, target points use a clear sequential schema indicating numeric increments alongside drive storage size descriptors (e.g., /srv/storage1_320g).
Create the designated hardware directory mount points:

sudo mkdir -p /srv/storage1_320g /srv/storage2_250g

Launch the core filesystem initialization mapping module using Vim:

sudo vim /etc/fstab

Vim Operational Execution Matrix:

   1. Press G to immediately advance your cursor timeline index to the absolute bottom line track.
   2. Press o to spin up a clean line and enter -- INSERT -- mode parameters.
   3. Paste the exact automated production configuration mapping statement block:

UUID=6F725C1264FDAFD4 /srv/storage1_320g ntfs-3g uid=1000,gid=1000,dmask=007,fmask=117,nofail 0 0


   1. Press Esc to safely drop out of execution modes, type :wq, and hit Enter to commit shifts to disk storage tracks.

Mount Parameter Explanations:

* UUID=6F725C1264FDAFD4: Targets the explicit storage disk securely, preventing drive letters from shifting if you change USB ports.
* ntfs-3g: Deploys the functional user-space execution driver engine enabling read/write paths.
* uid=1000,gid=1000: Passes absolute storage ownership privileges directly over to the main derril-piserver account profile.
* dmask=007,fmask=117: Restricts general public permissions while guaranteeing clean directory read/write access tools for the owner.
* nofail: Prevent system panic crashes or boot lockouts if the USB hardware gets temporarily unplugged during cold reboots.

Test the newly defined file system matrix maps and query the active capacity logs:

sudo mount -a
df -h /srv/storage1_320g

------------------------------
## ⚡ Hardware Safety Advisory: USB Power Limitations
When deploying multiple 2.5-inch external mechanical HDDs on a Raspberry Pi host node, you will hit power thresholds:

* The Problem: A standard 2.5" mechanical drive draws approximately 500mA to 1000mA (1 Amp) during peak track seek sequences. The Raspberry Pi shares a rigid total allocation constraint of 1.2 Amps across its four combined USB ports. Connecting two external drives simultaneously causes power drops, resetting the USB bus controller and dropping the drives from df -h.
* The Production Fix: You must offload power delivery tracks by running additional storage drives through an externally powered USB 3.0 Hub backed by a dedicated 5V/3A AC wall outlet power supply adapter unit.

------------------------------
## 🔒 Phase 2: Edge Network Integration via Cloudflare Tunnels
Instead of modifying consumer router configurations, opening vulnerable inbound network entry points, or dealing with dynamic DDNS IP updates, a production-grade Cloudflare Zero Trust Secure Outbound Tunnel (cloudflared) was deployed.
## 1. Removing Overlapping CNAME Traffic Pointers
Before running your automated tunnel routing configuration layers, any conflicting manual configurations must be cleaned out.

   1. Log into your Cloudflare Web Console Dashboard.
   2. Select your active domain site profile block: derrildsouza.com.
   3. Open DNS ➔ Records menu panels.
   4. Locate the old manual CNAME or A tracking record hooks pointing to your root domain (@) or www over toward DuckDNS subdomains.
   5. Click Delete on those entries to prevent routing rule conflicts.

## 2. Generating the Inbound Tunnel Pipeline

   1. Navigate to the Cloudflare Zero Trust Control Panel.
   2. Select Networks ➔ Tunnels on the sidebar workspace map interface, then choose Create a Tunnel.
   3. Choose Cloudflared (Recommended), tag your target asset tracker with an identifier name (e.g., Pi-CasaOS), and hit Save.

## 3. Native Connector Service Deployment (Apt Repository Pipeline)
To ensure the bridge client remains automatically updated through native package management pipelines, we configure Cloudflare's verified binary repository directly on the Pi.
Initialize the secure cryptographic key layout directories and install the tracking keys:

sudo mkdir -p --mode=0755 /usr/share/keyrings
curl -fsSL https://cloudflare.com | sudo tee /usr/share/keyrings/cloudflare-archive-keyring.gpg >/dev/null

Inject the repository path architecture definitions matching your system variant environment profiles:

echo "deb [signed-by=/usr/share/keyrings/cloudflare-archive-keyring.gpg] https://cloudflare.com $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/cloudflared.list

Execute a clean repository structural update index sync and deploy the compiled executable suite:

sudo apt update && sudo apt install cloudflared -y

## 4. Background Daemon System Registration
Inject your unique background service connector token to register the runtime daemon against Cloudflare's data centers:

sudo cloudflared service install YOUR_SECRET_TOKEN_STRING

(Replace YOUR_SECRET_TOKEN_STRING with the long, distinct cryptographic block provided by your dashboard setup panel).
Verify the native background environment service initialized correctly:

Using Systemd
Linux service for cloudflared installed successfully

The status flag inside your Zero Trust dashboard console screen will immediately shift to a healthy bright green HEALTHY / CONNECTED tracking metric.
## 5. Published Web Application Endpoint Routing Matrix
Map public internet traffic hits from your custom domain straight into the internal local system execution ports on the Pi server node.

   1. Navigate to the Published application routes tab layout section of your specific Pi-CasaOS tunnel control workspace.
   2. Click on the blue action control layout button labeled Add a published application route.
   3. Apply these exact operational configuration metrics inside the input data matrix fields:

┌───────────────────┬────────────────────────────────────────────────────────┐
│ Configuration Field│ Explicit Production Entry Assignment Parameter        │
├───────────────────┼────────────────────────────────────────────────────────┤
│ Subdomain         │ [Leave Completely Empty / Blank for Root Domain Mapping]│
│ Domain            │ derrildsouza.com                                       │
│ Path              │ [Leave Completely Empty / Blank to Forward All Paths]  │
│ Service Type      │ HTTP                                                   │
│ Service URL       │ localhost:80                                           │
└───────────────────┴────────────────────────────────────────────────────────┘


   1. Click Save at the absolute bottom right of the wizard screen.

------------------------------
## 🚀 Post-Deployment System Verification
The infrastructure ecosystem is now completely self-contained, automated, and resilient against power cycles.
## Automated Boot Verification Checklist:

* System Start-up Layer: The kernel mounts external storage directly to /srv/storage1_320g before user service initialization steps run.
* Network Interface Initialization: The cloudflared background service triggers automatically at boot, opening a secure outbound connection block to Cloudflare edge nodes.
* Application Layer Deployment: Docker and CasaOS spin up on internal loopback port 80.
* Dynamic DNS Autonomy: Because the tunnel points inside the local loopback space via localhost:80, your web domain address will never break, even if your home internet router shifts your internal IP address space!

## Final Verification Test
Disconnect an external device (like a smartphone) from your home network and switch to cellular data. Navigate directly to your secure URL profile:

https://derrildsouza.com

The browser will resolve past your ISP network layers, apply automated SSL certificate encryption routines, and display your CasaOS Server Login Dashboard Portal instantaneously from anywhere in the world.

